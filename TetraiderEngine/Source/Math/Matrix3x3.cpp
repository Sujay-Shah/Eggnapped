/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Author: <Holden Profit>
- End Header --------------------------------------------------------*/

#include <Stdafx.h>

Matrix3x3::Matrix3x3() {}

Matrix3x3::Matrix3x3(
	float x1, float y1, float z1, 
	float x2, float y2, float z2, 
	float x3, float y3, float z3)
{
	m_matrix[0][0] = x1;
	m_matrix[0][1] = y1;
	m_matrix[0][2] = z1;

	m_matrix[1][0] = x2;
	m_matrix[1][1] = y2;
	m_matrix[1][2] = z2;

	m_matrix[2][0] = x3;
	m_matrix[2][1] = y3;
	m_matrix[2][2] = z3;
}

Matrix3x3::Matrix3x3(const Matrix3x3 &other)
{
	m_matrix[0][0] = other.m_matrix[0][0];
	m_matrix[0][1] = other.m_matrix[0][1];
	m_matrix[0][2] = other.m_matrix[0][2];

	m_matrix[1][0] = other.m_matrix[1][0];
	m_matrix[1][1] = other.m_matrix[1][1];
	m_matrix[1][2] = other.m_matrix[1][2];

	m_matrix[2][0] = other.m_matrix[2][0];
	m_matrix[2][1] = other.m_matrix[2][1];
	m_matrix[2][2] = other.m_matrix[2][2];
}

Matrix3x3& Matrix3x3::operator=(const Matrix3x3& other)
{
	m_matrix[0][0] = other.m_matrix[0][0];
	m_matrix[0][1] = other.m_matrix[0][1];
	m_matrix[0][2] = other.m_matrix[0][2];

	m_matrix[1][0] = other.m_matrix[1][0];
	m_matrix[1][1] = other.m_matrix[1][1];
	m_matrix[1][2] = other.m_matrix[1][2];

	m_matrix[2][0] = other.m_matrix[2][0];
	m_matrix[2][1] = other.m_matrix[2][1];
	m_matrix[2][2] = other.m_matrix[2][2];
	return *this;
}

Matrix3x3::~Matrix3x3(){}

float Matrix3x3::Get(int row, int col) const
{
	return m_matrix[row][col];
}

void Matrix3x3::Set(int row, int col, float val)
{
	m_matrix[row][col] = val;
}

void Matrix3x3::Transpose()
{
	Matrix3x3 transposed = Matrix3x3(
		0.0f,			m_matrix[1][0], m_matrix[2][0],
		m_matrix[0][1], 0.0f,			m_matrix[2][1],
		m_matrix[0][2], m_matrix[1][2], 0.0f
	);

	m_matrix[0][1] = transposed.m_matrix[0][1];
	m_matrix[0][2] = transposed.m_matrix[0][2];

	m_matrix[1][0] = transposed.m_matrix[1][0];
	m_matrix[1][2] = transposed.m_matrix[1][2];

	m_matrix[2][0] = transposed.m_matrix[2][0];
	m_matrix[2][1] = transposed.m_matrix[2][1];
}

void Matrix3x3::Zero()
{
	m_matrix[0][0] = 0.0f;
	m_matrix[0][1] = 0.0f;
	m_matrix[0][2] = 0.0f;

	m_matrix[1][0] = 0.0f;
	m_matrix[1][1] = 0.0f;
	m_matrix[1][2] = 0.0f;

	m_matrix[2][0] = 0.0f;
	m_matrix[2][1] = 0.0f;
	m_matrix[2][2] = 0.0f;
}

void Matrix3x3::Identity()
{
	m_matrix[0][0] = 1.0f;
	m_matrix[0][1] = 0.0f;
	m_matrix[0][2] = 0.0f;

	m_matrix[1][0] = 0.0f;
	m_matrix[1][1] = 1.0f;
	m_matrix[1][2] = 0.0f;

	m_matrix[2][0] = 0.0f;
	m_matrix[2][1] = 0.0f;
	m_matrix[2][2] = 1.0f;
}

float Matrix3x3::Determinant() const
{
	return	m_matrix[0][0] * m_matrix[1][1] * m_matrix[2][2] +
			m_matrix[0][1] * m_matrix[1][2] * m_matrix[2][0] +
			m_matrix[0][2] * m_matrix[1][0] * m_matrix[2][1] -
			m_matrix[2][2] * m_matrix[1][1] * m_matrix[0][2] -
			m_matrix[2][1] * m_matrix[1][2] * m_matrix[0][0] -
			m_matrix[2][0] * m_matrix[1][0] * m_matrix[0][1];
}

void Matrix3x3::Print() const
{
	std::cout << "[ " << m_matrix[0][0] << ", " << m_matrix[0][1] << ", " << m_matrix[0][2] << "]" << std::endl;
	std::cout << "[ " << m_matrix[1][0] << ", " << m_matrix[1][1] << ", " << m_matrix[1][2] << "]" << std::endl;
	std::cout << "[ " << m_matrix[2][0] << ", " << m_matrix[2][1] << ", " << m_matrix[2][2] << "]" << std::endl;
}

#pragma region Static Methods
Matrix3x3 Matrix3x3::Zero3D()
{
	return Matrix3x3(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
}

Matrix3x3 Matrix3x3::Identity3D()
{
	return Matrix3x3(
		1.0f, 0.0f, 0.0f, 
		0.0f, 1.0f, 0.0f, 
		0.0f, 0.0f, 1.0f
	);
}

float Matrix3x3::Determinant(const Matrix3x3& other)
{
	return	other.m_matrix[0][0] * other.m_matrix[1][1] * other.m_matrix[2][2] +
			other.m_matrix[0][1] * other.m_matrix[1][2] * other.m_matrix[2][0] +
			other.m_matrix[0][2] * other.m_matrix[1][0] * other.m_matrix[2][1] -
			other.m_matrix[2][2] * other.m_matrix[1][1] * other.m_matrix[0][2] -
			other.m_matrix[2][1] * other.m_matrix[1][2] * other.m_matrix[0][0] -
			other.m_matrix[2][0] * other.m_matrix[1][0] * other.m_matrix[0][1];
}


Matrix3x3 Matrix3x3::Translate(float x, float y)
{
	return Matrix3x3(
		1.0f, 0.0f, x,
		0.0f, 1.0f, y,
		0.0f, 0.0f, 1.0f
	);
}

Matrix3x3 Matrix3x3::Scale(float x, float y)
{
	return Matrix3x3(
		x, 0.0f, 0.0f,
		0.0f, y, 0.0f,
		0.0f, 0.0f, 1.0f
	);
}

Matrix3x3 Matrix3x3::RotateDeg_Z(float degrees)
{
	return RotateRad_Z(degrees * DEG_TO_RAD);
}

Matrix3x3 Matrix3x3::RotateRad_Z(float radians)
{
	return Matrix3x3(
		cosf(radians), -sinf(radians), 0.0f,
		sinf(radians), cosf(radians), 0.0f,
		0.0f, 0.0f, 1.0f
	);
}
#pragma endregion

#pragma region Operation Overrides
bool Matrix3x3::operator==(const Matrix3x3& other)
{
	double d = 0.0f;

	d += fabs(m_matrix[0][0] - other.m_matrix[0][0]);
	d += fabs(m_matrix[0][1] - other.m_matrix[0][1]);
	d += fabs(m_matrix[0][2] - other.m_matrix[0][2]);

	d += fabs(m_matrix[1][0] - other.m_matrix[1][0]);
	d += fabs(m_matrix[1][1] - other.m_matrix[1][1]);
	d += fabs(m_matrix[1][2] - other.m_matrix[1][2]);

	d += fabs(m_matrix[2][0] - other.m_matrix[2][0]);
	d += fabs(m_matrix[2][1] - other.m_matrix[2][1]);
	d += fabs(m_matrix[2][2] - other.m_matrix[2][2]);
	return d < EPSILON;
}

bool Matrix3x3::operator!=(const Matrix3x3& other)
{
	double d = 0.0f;

	d += fabs(m_matrix[0][0] - other.m_matrix[0][0]);
	d += fabs(m_matrix[0][1] - other.m_matrix[0][1]);
	d += fabs(m_matrix[0][2] - other.m_matrix[0][2]);

	d += fabs(m_matrix[1][0] - other.m_matrix[1][0]);
	d += fabs(m_matrix[1][1] - other.m_matrix[1][1]);
	d += fabs(m_matrix[1][2] - other.m_matrix[1][2]);

	d += fabs(m_matrix[2][0] - other.m_matrix[2][0]);
	d += fabs(m_matrix[2][1] - other.m_matrix[2][1]);
	d += fabs(m_matrix[2][2] - other.m_matrix[2][2]);
	return d >= EPSILON;
}

Matrix3x3 Matrix3x3::operator+(const Matrix3x3& other)
{
	return Matrix3x3(
		m_matrix[0][0] + other.m_matrix[0][0], m_matrix[0][1] + other.m_matrix[0][1], m_matrix[0][2] + other.m_matrix[0][2],
		m_matrix[1][0] + other.m_matrix[1][0], m_matrix[1][1] + other.m_matrix[1][1], m_matrix[1][2] + other.m_matrix[1][2],
		m_matrix[2][0] + other.m_matrix[2][0], m_matrix[2][1] + other.m_matrix[2][1], m_matrix[2][2] + other.m_matrix[2][2]
	);
}

Matrix3x3 Matrix3x3::operator-(const Matrix3x3& other)
{
	return Matrix3x3(
		m_matrix[0][0] - other.m_matrix[0][0], m_matrix[0][1] - other.m_matrix[0][1], m_matrix[0][2] - other.m_matrix[0][2],
		m_matrix[1][0] - other.m_matrix[1][0], m_matrix[1][1] - other.m_matrix[1][1], m_matrix[1][2] - other.m_matrix[1][2],
		m_matrix[2][0] - other.m_matrix[2][0], m_matrix[2][1] - other.m_matrix[2][1], m_matrix[2][2] - other.m_matrix[2][2]
	);
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& other)
{
	return Matrix3x3(
		(m_matrix[0][0] * other.m_matrix[0][0]) + (m_matrix[0][1] * other.m_matrix[1][0]) + (m_matrix[0][2] * other.m_matrix[2][0]),
		(m_matrix[0][0] * other.m_matrix[0][1]) + (m_matrix[0][1] * other.m_matrix[1][1]) + (m_matrix[0][2] * other.m_matrix[2][1]),
		(m_matrix[0][0] * other.m_matrix[0][2]) + (m_matrix[0][1] * other.m_matrix[1][2]) + (m_matrix[0][2] * other.m_matrix[2][2]),

		(m_matrix[1][0] * other.m_matrix[0][0]) + (m_matrix[1][1] * other.m_matrix[1][0]) + (m_matrix[1][2] * other.m_matrix[2][0]),
		(m_matrix[1][0] * other.m_matrix[0][1]) + (m_matrix[1][1] * other.m_matrix[1][1]) + (m_matrix[1][2] * other.m_matrix[2][1]),
		(m_matrix[1][0] * other.m_matrix[0][2]) + (m_matrix[1][1] * other.m_matrix[1][2]) + (m_matrix[1][2] * other.m_matrix[2][2]),

		(m_matrix[2][0] * other.m_matrix[0][0]) + (m_matrix[2][1] * other.m_matrix[1][0]) + (m_matrix[2][2] * other.m_matrix[2][0]),
		(m_matrix[2][0] * other.m_matrix[0][1]) + (m_matrix[2][1] * other.m_matrix[1][1]) + (m_matrix[2][2] * other.m_matrix[2][1]),
		(m_matrix[2][0] * other.m_matrix[0][2]) + (m_matrix[2][1] * other.m_matrix[1][2]) + (m_matrix[2][2] * other.m_matrix[2][2])
	);
}

Matrix3x3 Matrix3x3::operator*(const float scalar)
{
	return Matrix3x3(
		m_matrix[0][0] * scalar, m_matrix[0][1] * scalar, m_matrix[0][2] * scalar,
		m_matrix[1][0] * scalar, m_matrix[1][1] * scalar, m_matrix[1][2] * scalar,
		m_matrix[2][0] * scalar, m_matrix[2][1] * scalar, m_matrix[2][2] * scalar
	);
}

Matrix3x3 Matrix3x3::operator/(const float divisor)
{
	return Matrix3x3(
		m_matrix[0][0] / divisor, m_matrix[0][1] / divisor, m_matrix[0][2] / divisor,
		m_matrix[1][0] / divisor, m_matrix[1][1] / divisor, m_matrix[1][2] / divisor,
		m_matrix[2][0] / divisor, m_matrix[2][1] / divisor, m_matrix[2][2] / divisor
	);
}


Vector2D Matrix3x3::operator*(const Vector2D& other)
{
	return Vector2D(
		m_matrix[0][0] * other.x + m_matrix[0][1] * other.y + m_matrix[0][2] * other.w,
		m_matrix[1][0] * other.x + m_matrix[1][1] * other.y + m_matrix[1][2] * other.w,
		m_matrix[2][0] * other.x + m_matrix[2][1] * other.y + m_matrix[2][2] * other.w
	);
}


Vector3D Matrix3x3::operator*(const Vector3D& other)
{
	return Vector3D(
		m_matrix[0][0] * other.x + m_matrix[0][1] * other.y + m_matrix[0][2] * other.z,
		m_matrix[1][0] * other.x + m_matrix[1][1] * other.y + m_matrix[1][2] * other.z,
		m_matrix[2][0] * other.x + m_matrix[2][1] * other.y + m_matrix[2][2] * other.z
	);
}
#pragma endregion

#if TEST_MODE
void Matrix3x3Tests()
{
	std::cout << "\n========== Running Matrix3x3 tests ==========\n\n";

#pragma region Methods
	Matrix3x3 m0 = Matrix3x3();
	Matrix3x3 m1 = Matrix3x3();
	long i, j;

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			m0.Set(i, j, float(i * 2 + j));
			m1.Set(i, j, float(i + j * 2));
		}
	}

	m1.Transpose();
	std::cout << "Matrix3x3 Transpose: " << ((m0 == m1) ? PASS : FAIL) << std::endl;

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			m0.Set(i, j, 0.0f);
		}
	}
	m1.Zero();
	std::cout << "Matrix3x3 Zero: " << ((m0 == m1) ? PASS : FAIL) << std::endl;

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			m0.Set(i, j, i == j ? 1.0f : 0.0f);
		}
	}

	m1.Identity();
	std::cout << "Matrix3x3 Identity: " << ((m0 == m1) ? PASS : FAIL) << std::endl;
#pragma endregion
#pragma region StaticMethods
	m0.Zero();

	Matrix3x3 zero = Matrix3x3::Zero3D();
	std::cout << "Matrix3x3::Zero: " << ((zero == m0) ? PASS : FAIL) << std::endl;

	m0.Identity();

	Matrix3x3 identity = Matrix3x3::Identity3D();
	std::cout << "Matrix3x3::Identity: " << ((m0 == identity) ? PASS : FAIL) << std::endl;
#pragma endregion

#pragma region Operations

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			m0.Set(i, j, float(i + j));
			m1.Set(i, j, float(i - j));
		}
	}
	std::cout << "Matrix3x3 == Matrix3x3 equal: " << ((m0 == m0) ? PASS : FAIL) << std::endl;

	std::cout << "Matrix3x3 == Matrix3x3 not equal: " << ((m0 == m1) ? FAIL : PASS);

	std::cout << "Matrix3x3 != Matrix3x3 not equal: " << ((m0 != m1) ? PASS : FAIL) << std::endl;

	std::cout << "Matrix3x3 != Matrix3x3 equal: " << ((m0 != m0) ? FAIL : PASS);

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			m0.Set(i, j, float(i + j));
			m1.Set(i, j, float(-(i + j)));
		}
	}
	std::cout << "Matrix3x3 + Matrix3x3: " << ((zero == m0 + m1) ? PASS : FAIL) << std::endl;

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			m0.Set(i, j, float(i + j));
			m1.Set(i, j, float(i + j));
		}
	}
	std::cout << "Matrix3x3 - Matrix3x3: " << ((zero == m0 - m1) ? PASS : FAIL) << std::endl;

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			m0.Set(i, j, float(i + j));
			m1.Set(i, j, float(i + j));
		}
	}
	Matrix3x3 result = Matrix3x3(5.0f, 8.0f, 11.0f, 8.0f, 14.0f, 20.0f, 11.0f, 20.0f, 29.0f);
	std::cout << "Matrix3x3 * Matrix3x3: " << ((m0 * m1 == result) ? PASS : FAIL) << std::endl;

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			m0.Set(i, j, float(i + j));
			m1.Set(i, j, float((i + j) * 2.0f));
		}
	}
	std::cout << "Matrix3x3 * scalar: " << (((m0 * 2.0f) == m1) ? PASS : FAIL) << std::endl;

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			m0.Set(i, j, float(i + j));
			m1.Set(i, j, float((i + j) / 2.0f));
		}
	}
	std::cout << "Matrix3x3 / divisor: " << (((m0 / 2.0f) == m1) ? PASS : FAIL) << std::endl;
#pragma endregion
#pragma region Vector2D
	std::cout << "\n========== Running Matrix3x3 - Vector2D tests ==========\n\n";
	Matrix3x3 x22 = Matrix3x3(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
	Vector2D v2 = Vector2D(1.0f, 2.0f, 1.0f);
	Vector2D v2Test = Vector2D(8.0f, 20.0f, 32.0f);
	std::cout << "Matrix3x3 * Vector2D: " << ((v2Test == (x22 * v2)) ? PASS : FAIL) << std::endl;
#pragma endregion

#pragma region Vector3D
	std::cout << "\n========== Running Matrix3x3 - Vector3D tests ==========\n\n";
	Matrix3x3 x33 = Matrix3x3(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
	Vector3D v3 = Vector3D(1.0f, 2.0f, 3.0f);
	Vector3D v3Test = Vector3D(14.0f, 32.0f, 50.0f);
	std::cout << "Matrix3x3 * Vector3D: " << ((v3Test == (x33 * v3)) ? PASS : FAIL) << std::endl;
#pragma endregion
}
#endif