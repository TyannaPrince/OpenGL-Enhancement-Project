/*****************************************************************
 *   Author: Tyanna Prince
 *   Date: 07/15/2023
 *   Description: An enhancement of my cs330 OpenGL project where I added functionality such as charater movement,
 *  directional lighting, and shadow mapping, a cubemap, and joystick support.
 *  copyright (c) 2023 Tyanna Prince
 *  version 2.0
 *****************************************************************/

#include "linalg.h"

#include <limits>
#include <glm/glm.hpp>

/*
    Line-plane intersection cases
    PI is the plane containing the vectors P1P2 and P1P3

    CASE 0
        line U1U2 lies in the plane PI
        t = 0 / 0

    CASE 1
        no planar intersection
        t = (R != 0) / 0

        => intersection when
        !(tnum != 0 && tden == 0)
        = tnum == 0 || tden != 0 (DeMorgan)

    CASE 2
        planar intersection, in between U1 and U2
        t = R / (R != 0) in the range [0, 1]

    CASE 3
        planar intersection, outside of U1 and U2
        t = R / (R != 0) not in the range [0, 1]
*/

/**
 * Calculates the parameter t of the line { U1 + side * t } at the point of intersection between a line and a plane.
 *
 * @param P1 The point on the line.
 * @param norm The normal vector of the plane.
 * @param U1 The starting point of the line.
 * @param side The direction vector of the line.
 * @param t Reference to store the calculated value of t.
 *
 * @return The case of the intersection:
 *         - LinePlaneIntCase::CASE0 if the line is parallel to the plane and lies on the plane.
 *         - LinePlaneIntCase::CASE1 if the line is parallel to the plane and does not lie on the plane.
 *         - LinePlaneIntCase::CASE2 if the line intersects the plane within the line segment defined by U1 and U1 + side.
 *         - LinePlaneIntCase::CASE3 if the line does not intersect the plane within the line segment defined by U1 and U1 + side.
 *
 * @throws None.
 */
LinePlaneIntCase linePlaneIntersection(glm::vec3 P1, glm::vec3 norm, glm::vec3 U1, glm::vec3 side, float& t) {
    // calculate the parameter t of the line { U1 + side * t } at the point of intersection
    /*
        t = (N dot U1P1) / (N dot U1U2)
    */
    glm::vec3 U1P1 = P1 - U1;

    float tnum = glm::dot(norm, U1P1);
    float tden = glm::dot(norm, side);

    if (tden == 0.0f) {
        return tnum == 0.0f ? LinePlaneIntCase::CASE0 : LinePlaneIntCase::CASE1;
    }
    else {
        // can do division
        t = tnum / tden;
        return t >= 0.0f && t <= 1.0f ? LinePlaneIntCase::CASE2 : LinePlaneIntCase::CASE3;
    }
}

/**
 * Multiplies a 4x4 matrix by a 3D vector and returns the result.
 *
 * @param m The 4x4 matrix to be multiplied.
 * @param v The 3D vector to be multiplied.
 *
 * @return The resulting 3D vector.
 *
 * @throws None.
 */
glm::vec3 mat4vec3mult(glm::mat4& m, glm::vec3& v) {
    glm::vec3 ret;
    for (int i = 0; i < 3; i++) {
        ret[i] = v[0] * m[0][i] + v[1] * m[1][i] + v[2] * m[2][i] + m[3][i];
    }
    return ret;
}

/**
 * Calculate the solution to a system of linear equations using linear combination.
 *
 * @param A The first basis vector.
 * @param B The second basis vector.
 * @param C The third basis vector.
 * @param point The point to be represented as a linear combination of the basis vectors.
 * 
 * @return The solution to the system of linear equations.
 * 
 * @throws None.
 */
glm::vec3 linCombSolution(glm::vec3 A, glm::vec3 B, glm::vec3 C, glm::vec3 point) {
    // represent the point as a linear combination of the 3 basis vectors
    glm::mat4x3 m(A, B, C, point);

    // do RREF
    rref<4, 3>(m);

    return m[3];
}

/**
 * Checks if a point is within a range defined by three vertices of a triangle.
 *
 * @param A The first vertex of the triangle.
 * @param B The second vertex of the triangle.
 * @param N The normal vector of the triangle.
 * @param point The point to be checked.
 * @param radius The radius of the range around the triangle.
 *
 * @return True if the point is within the range, false otherwise.
 *
 * @throws None.
 */
bool faceContainsPointRange(glm::vec3 A, glm::vec3 B, glm::vec3 N, glm::vec3 point, float radius) {
    glm::vec3 c = linCombSolution(A, B, N, point);

    return c[0] >= -radius && c[1] >= -radius && c[0] + c[1] <= 1.0f + radius;
}

/**
 * Check if a given point is contained within a face defined by three vertices.
 *
 * @param A The first vertex of the face.
 * @param B The second vertex of the face.
 * @param N The normal vector of the face.
 * @param point The point to check.
 *
 * @return True if the point is contained in the face, false otherwise.
 *
 * @throws None.
 */
bool faceContainsPoint(glm::vec3 A, glm::vec3 B, glm::vec3 N, glm::vec3 point) {
    return faceContainsPointRange(A, B, N, point, 0.0f);
}
