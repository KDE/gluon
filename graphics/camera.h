/*
 * Copyright (C) 2008 Rivo Laks <rivolaks@hot.ee>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef GLUON_GRAPHICS_CAMERA_H
#define GLUON_GRAPHICS_CAMERA_H

#include <QtCore/QObject>
#include <Eigen/Geometry>

#include "gluon_graphics_export.h"

namespace GluonGraphics
{

//TODO: Move private members to private class
class GLUON_GRAPHICS_EXPORT Camera : public QObject
{
    /**
     * @brief Camera class.
     *
     * Camera represents a virtual camera that can be used to view a scene.
     *
     * Camera's parameters can be specified in two ways:
     * Usually you will use the @ref setPosition, @ref setUp and either
     *  @ref setLookAt or @ref setDirection to set up camera position. The
     *  perspective transformation is specified using @ref setFoV, @ref setAspect
     *  and @ref setDepthRange methods.
     *
     * Alternatively, you can specify the modelview and projection matrices
     *  directly, using @ref setModelviewMatrix and @ref setProjectionMatrix
     *  methods.
     *
     * You can also use one way for the modelview matrix and another way for the
     *  projection matrix.
     * You can't mix the two modes though. If you use @ref setModelviewMatrix()
     *  and then @ref setPosition() then the setModelviewMatrix() call has no
     *  effect and modelview matrix will be calculated using specified position,
     *  lookat and up vectors.
     *
     * Camera also takes care of viewport handling. Instead of calling
     *  glViewport() directly, you should use @ref setViewport() and
     *  @ref applyViewport() methods.
     *
     * Finally, Camera has @ref project() and @ref unProject() methods for
     *  projecting points from world coordinates to window coordinates and vice
     *  versa. Obviously it only works if you don't modify OpenGL matrices or
     *  viewport manually but use the methods of this class instead.
     **/
    Q_OBJECT

    public:
        Camera();
        virtual ~Camera();

        Eigen::Vector3f position() const  { return mPosition; }
        Eigen::Vector3f lookAt() const  { return mLookAt; }
        Eigen::Vector3f up() const  { return mUp; }

        /**
        * @return current modelview matrix.
        * Modelview matrix is either set using the @ref setModelviewMatrix method
        *  or automatically calculated using position, lookAt and up vectors.
        **/
        Eigen::Transform3f modelviewMatrix() const;
        /**
        * @return current projection matrix.
        * Projection matrix is either set using the @ref setProjectionMatrix
        *   method or automatically calculated using fov, aspect and depth range
        *   parameters.
        **/
        Eigen::Transform3f projectionMatrix() const;

        /**
        * Transforms vector @p v from world coordinates to window coordinates.
        *
        * If @p ok is not null then it will be set to true or false depending on
        *  whether the projection was successful or not.
        **/
        Eigen::Vector3f project(const Eigen::Vector3f& v, bool* ok = 0) const;
        /**
        * Transforms vector @p v from window coordinates to world coordinates.
        *
        * If @p ok is not null then it will be set to true or false depending on
        *  whether the projection was successful or not.
        **/
        Eigen::Vector3f unProject(const Eigen::Vector3f& v, bool* ok = 0) const;

    public slots:
        /**
         * Applies the camera's projection matrix.
         *
         * Any current perspective transformations will be lost.
         **/
        virtual void applyPerspective();
        
        virtual void applyOrtho();
        /**
         * Applies the camera's modelview matrix.
         *
         * @param reset if true then glLoadIdentity() is called before applying.
         *  This ensures that current transformations won't affect the camera.
         **/
        virtual void applyView(bool reset = true);

        /**
         * Applies the viewport that has been specified using the @ref setViewport
         *  method.
         **/
        virtual void applyViewport();

        /**
         * Specifies the current viewport.
         **/
        void setViewport(int x, int y, int width, int height);

        /**
         * Sets the vertical field-of-view angle in degrees to @p fov.
         **/
        void setFoV(float fov);
        /**
         * Sets the aspect ration to @p aspect.
         * Aspect ratio is usually window's width divided by its height.
         **/
        void setAspect(float aspect);
        /**
         * Sets the depth buffer's range.
         *
         * @p near is distance from the camera to the near clipping plane and
         *  @p far is distance to the far clipping plane. Everything that is not
         *  between those two planes will be clipped away (not rendered), so you
         *  should make sure that all your objects are within that range.
         * At the same time, the depth range should be as small as possible (i.e.
         *  @p near should be as big and @p far as small as possible) to increase
         *  depth buffer precision.
         **/
        void setDepthRange(float near, float far);

        /**
         * Sets the camera's positionto @p pos.
         **/
        void setPosition(const Eigen::Vector3f& pos);
        void setPosition(float x, float y, float z)  { setPosition(Eigen::Vector3f(x, y, z)); }
        /**
         * Sets the lookat point to @p lookat.
         * LookAt is the point at which the camera is looking at.
         **/
        void setLookAt(const Eigen::Vector3f& lookat);
        void setLookAt(float x, float y, float z)  { setLookAt(Eigen::Vector3f(x, y, z)); }
        /**
         * Sets the up vector to @p up.
         * Up vector is the one pointing upwards in the viewport.
         **/
        void setUp(const Eigen::Vector3f& up);
        void setUp(float x, float y, float z)  { setUp(Eigen::Vector3f(x, y, z)); }
        /**
         * Sets the viewing direction of the camera to @p dir.
         * This method sets lookat point to @ref position() + dir, thus
         *  you will need to set camera's position before using this method.
         **/
        void setDirection(const Eigen::Vector3f& dir);
        void setDirection(float x, float y, float z)  { setDirection(Eigen::Vector3f(x, y, z)); }

        /**
         * Sets the modelview matrix.
         *
         * If you specify the modelview matrix using this method then parameters
         *  specified using @ref setPosition, @ref setLookAt and @ref setUp
         *  methods will be ignored.
         *
         * If you call any of @ref setPosition, @ref setLookAt or @ref setUp
         *  after calling this method, then the modelview matrix specified here
         *  will be ignored and new modelview matrix will be calculated using
         *  specified position, lookat and up vectors.
         **/
        void setModelviewMatrix(const Eigen::Transform3f& modelview);
        /**
         * Sets the projection matrix.
         *
         * If you specify the projection matrix using this method then parameters
         *  specified using @ref setFoV, @ref setAspect and @ref setDepthRange
         *  methods will be ignored.
         *
         * If you call any of @ref setFoV, @ref setAspect or @ref setDepthRange
         *  after calling this method, then the projection matrix specified here
         *  will be ignored and new projection matrix will be calculated using
         *  specified fov, aspect and depth range parameters.
         **/
        void setProjectionMatrix(const Eigen::Transform3f& projection);

    protected:
        void recalculateModelviewMatrix();
        void recalculateProjectionMatrix();

    protected:
        Eigen::Vector3f mPosition;
        Eigen::Vector3f mLookAt;
        Eigen::Vector3f mUp;
        float mFoV, mAspect, mDepthNear, mDepthFar;

        Eigen::Transform3f mModelviewMatrix;
        bool mModelviewMatrixDirty;
        Eigen::Transform3f mProjectionMatrix;
        bool mProjectionMatrixDirty;
        int mViewport[4];
    };

}




#endif // GLUON_GRAPHICS_CAMERA_H
