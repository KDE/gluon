#include "camera.h"
#include <math.h>

#include <glew.h>



using namespace GluonGraphics;

Camera::Camera()
{
    mFoV = 45.0f;
    mAspect = 1.0f;
    mDepthNear = -1000.0f;
    mDepthFar = 1000.0f;
    mPosition = QVector3D(0, 0, 100);
    mLookAt = QVector3D(0, 0, -1);
    mUp = QVector3D(0, 1, 0);
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

void Camera::setPosition(const QVector3D& pos)
{
    mPosition = pos;
    mModelviewMatrixDirty = true;
}

void Camera::setLookAt(const QVector3D& lookat)
{
    mLookAt = lookat;
    mModelviewMatrixDirty = true;
}

void Camera::setUp(const QVector3D& up)
{
    mUp = up;
    mModelviewMatrixDirty = true;
}

void Camera::setDirection(const QVector3D& dir)
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
    glMultMatrixd((GLdouble*)(mProjectionMatrix.data()));
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
    glMultMatrixd((GLdouble*)(mModelviewMatrix.data()));
}

void Camera::applyViewport()
{
    glViewport(mViewport[0], mViewport[1], mViewport[2], mViewport[3]);
}

void Camera::recalculateModelviewMatrix()
{
     // Code from Mesa project, src/glu/sgi/libutil/project.c
    mModelviewMatrixDirty = false;
    QVector3D forward = mLookAt.normalized();
    QVector3D side = -QVector3D::crossProduct(forward, mUp).normalized();
    QVector3D up = QVector3D::crossProduct(side,forward);

    mModelviewMatrix.setToIdentity();
    mModelviewMatrix.setColumn(0, QVector4D(side.x(),side.y(),side.z(),0));
    mModelviewMatrix.setColumn(1, QVector4D(up.x(),up.y(),up.z(),0));
    mModelviewMatrix.setColumn(2, QVector4D(-forward.x(),-forward.y(),-forward.z(),0));
    mModelviewMatrix.translate(mPosition);
}

void Camera::recalculateProjectionMatrix()
{
    // Code from Mesa project, src/glu/sgi/libutil/project.c
    mProjectionMatrixDirty = false;
    mProjectionMatrix.setToIdentity();

    float radians = mFoV / 2 * M_PI / 180;

    float deltaZ = mDepthFar - mDepthNear;
//    float sine = Eigen::ei_sin(radians);
     float sine = sin(radians);
    if ((deltaZ == 0) || (sine == 0) || (mAspect == 0)) {
        return;
    }
//    float cotangent = Eigen::ei_cos(radians) / sine;
      float cotangent = cos(radians) / sine;



    mProjectionMatrix(0, 0) = cotangent / mAspect;
    mProjectionMatrix(1, 1) = cotangent;
    mProjectionMatrix(2, 2) = -(mDepthFar + mDepthNear) / deltaZ;
    mProjectionMatrix(3, 2) = -1;
    mProjectionMatrix(2, 3) = -2 * mDepthNear * mDepthFar / deltaZ;
    mProjectionMatrix(3, 3) = 0;

    //glO
    //mProjectionMatrix.
}

void Camera::setModelviewMatrix(const QMatrix4x4& modelview)
{
    mModelviewMatrix = modelview;
    mModelviewMatrixDirty = false;
}

void Camera::setProjectionMatrix(const QMatrix4x4& projection)
{
    mProjectionMatrix = projection;
    mProjectionMatrixDirty = false;
}

QMatrix4x4 Camera::modelviewMatrix() const
{
    if (mModelviewMatrixDirty) {
        const_cast<Camera*>(this)->recalculateModelviewMatrix();
    }
    return mModelviewMatrix;
}

QMatrix4x4 Camera::projectionMatrix() const
{
    if (mProjectionMatrixDirty) {
        const_cast<Camera*>(this)->recalculateProjectionMatrix();
    }
    return mProjectionMatrix;
}

QVector3D Camera::project(const QVector3D& v, bool* ok) const
{
    // TODO add unit test
//    QVector3D res;
//    QVector4D p4 = projectionMatrix() * (modelviewMatrix() * QVector4D(v[0],v[1],v[2],1));
//    if (p4.w()!=0)
//    {
//      res = p4.start<3>() / p4.w();
//      res = (res * 0.5).cwise() + 0.5;
//      res.start<2>() = Eigen::Vector2f(mViewport[0],mViewport[1])
//                       + Eigen::Vector2f(mViewport[2],mViewport[3]).cwise() * res.start<2>();
//      if (ok)
//          *ok = true;
//    }
//    else if (ok)
//        *ok = false;
//    return res;
}

QVector3D Camera::unProject(const QVector3D& v, bool* ok) const
{
    // TODO add unit test
/*   if (ok) *ok = true;
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
    return a.start<3>() / a.w();*/
}

#include "camera.moc"
