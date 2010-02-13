#include "camera.h"
#include <math.h>

#include <glew.h>

#include <Eigen/LU>

using namespace GluonGraphics;

Camera::Camera()
{
    mFoV = 45.0f;
    mAspect = 1.0f;
    mDepthNear = -1000.0f;
    mDepthFar = 1000.0f;
    mPosition = Eigen::Vector3f(0, 0, 0);
    mLookAt = Eigen::Vector3f(0, 0, -1);
    mUp = Eigen::Vector3f(0, 1, 0);
    mModelviewMatrixDirty = true;
    mProjectionMatrixDirty = true;
}

Camera::~Camera()
{
}

void Camera::setFoV(float fov)
{
    mFoV = fov;
    mProjectionMatrixDirty = true;
}

void Camera::setAspect(float aspect)
{
    mAspect = aspect;
    mProjectionMatrixDirty = true;
}

void Camera::setDepthRange(float near, float far)
{
    mDepthNear = near;
    mDepthFar = far;
    mProjectionMatrixDirty = true;
}

void Camera::setPosition(const Eigen::Vector3f& pos)
{
    mPosition = pos;
    mModelviewMatrixDirty = true;
}

void Camera::setLookAt(const Eigen::Vector3f& lookat)
{
    mLookAt = lookat;
    mModelviewMatrixDirty = true;
}

void Camera::setUp(const Eigen::Vector3f& up)
{
    mUp = up;
    mModelviewMatrixDirty = true;
}

void Camera::setDirection(const Eigen::Vector3f& dir)
{
    setLookAt(mPosition + dir);
}

void Camera::setViewport(int x, int y, int width, int height)
{
    mViewport[0] = x;
    mViewport[1] = y;
    mViewport[2] = width;
    mViewport[3] = height;
}

void Camera::applyPerspective()
{
    if (mProjectionMatrixDirty) {
        recalculateProjectionMatrix();
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMultMatrixf(mProjectionMatrix.data());
    //glOrtho(, 5, -5, 5, mDepthNear, mDepthFar);
    glMatrixMode(GL_MODELVIEW);
}

void Camera::applyOrtho()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float left = mViewport[0] / 10.0f - mViewport[2] / 20.0f;
    float right = (mViewport[0] + mViewport[2]) / 20.0f;
    float top = mViewport[1] / 10.0f - mViewport[3] / 20.0f;
    float bottom = (mViewport[1] + mViewport[3]) / 20.0f;

    glOrtho(left, right, top, bottom, mDepthNear, mDepthFar);
    glMatrixMode(GL_MODELVIEW);
}

void Camera::applyView(bool reset)
{
    if (mModelviewMatrixDirty) {
        recalculateModelviewMatrix();
    }

    if (reset) {
        glLoadIdentity();
    }
    glMultMatrixf(mModelviewMatrix.data());
}

void Camera::applyViewport()
{
    glViewport(mViewport[0], mViewport[1], mViewport[2], mViewport[3]);
}

void Camera::recalculateModelviewMatrix()
{
    // Code from Mesa project, src/glu/sgi/libutil/project.c
    mModelviewMatrixDirty = false;
    // Our looking direction
    Eigen::Vector3f forward = mLookAt.normalized();

    Eigen::Vector3f side = forward.cross(mUp).normalized();

    // Recompute up vector, using cross product
    Eigen::Vector3f up = side.cross(forward);

    mModelviewMatrix.setIdentity();
    mModelviewMatrix.linear() << side.transpose(), up.transpose(), -forward.transpose();
    mModelviewMatrix.translate(-mPosition);
}

void Camera::recalculateProjectionMatrix()
{
    // Code from Mesa project, src/glu/sgi/libutil/project.c
    mProjectionMatrixDirty = false;
    mProjectionMatrix.setIdentity();

    float radians = mFoV / 2 * M_PI / 180;

    float deltaZ = mDepthFar - mDepthNear;
    float sine = Eigen::ei_sin(radians);
    if ((deltaZ == 0) || (sine == 0) || (mAspect == 0)) {
        return;
    }
    float cotangent = Eigen::ei_cos(radians) / sine;

    mProjectionMatrix(0, 0) = cotangent / mAspect;
    mProjectionMatrix(1, 1) = cotangent;
    mProjectionMatrix(2, 2) = -(mDepthFar + mDepthNear) / deltaZ;
    mProjectionMatrix(3, 2) = -1;
    mProjectionMatrix(2, 3) = -2 * mDepthNear * mDepthFar / deltaZ;
    mProjectionMatrix(3, 3) = 0;

    //glO
    //mProjectionMatrix.
}

void Camera::setModelviewMatrix(const Eigen::Transform3f& modelview)
{
    mModelviewMatrix = modelview;
    mModelviewMatrixDirty = false;
}

void Camera::setProjectionMatrix(const Eigen::Transform3f& projection)
{
    mProjectionMatrix = projection;
    mProjectionMatrixDirty = false;
}

Eigen::Transform3f Camera::modelviewMatrix() const
{
    if (mModelviewMatrixDirty) {
        const_cast<Camera*>(this)->recalculateModelviewMatrix();
    }
    return mModelviewMatrix;
}

Eigen::Transform3f Camera::projectionMatrix() const
{
    if (mProjectionMatrixDirty) {
        const_cast<Camera*>(this)->recalculateProjectionMatrix();
    }
    return mProjectionMatrix;
}

Eigen::Vector3f Camera::project(const Eigen::Vector3f& v, bool* ok) const
{
    // TODO add unit test
    Eigen::Vector3f res;
    Eigen::Vector4f p4 = projectionMatrix() * (modelviewMatrix() * Eigen::Vector4f(v[0],v[1],v[2],1));
    if (p4.w()!=0)
    {
      res = p4.start<3>() / p4.w();
      res = (res * 0.5).cwise() + 0.5;
      res.start<2>() = Eigen::Vector2f(mViewport[0],mViewport[1])
                       + Eigen::Vector2f(mViewport[2],mViewport[3]).cwise() * res.start<2>();
      if (ok)
          *ok = true;
    }
    else if (ok)
        *ok = false;
    return res;
}

Eigen::Vector3f Camera::unProject(const Eigen::Vector3f& v, bool* ok) const
{
    // TODO add unit test
    if (ok) *ok = true;
    Eigen::Vector4f a;
    a << (v.start<2>() - Eigen::Vector2f(mViewport[0],mViewport[1]))
              .cwise() / Eigen::Vector2f(mViewport[2],mViewport[3]),
         v.z(),
         1;
    a.start<3>() = a.start<3>() * 2 - Eigen::Vector3f::Constant(1);
    // FIXME if we assume the projection matrix always has the structure defined in
    // recalculateProjectionMatrix, then the following matrix product could be
    // significantly improved !!
    a = (projectionMatrix() * modelviewMatrix()).inverse() * a;
    if (a.w()==0)
    {
        if (ok) *ok = false;
        return a.start<3>();
    }
    return a.start<3>() / a.w();
}

#include "camera.moc"
