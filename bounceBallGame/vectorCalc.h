
#include <iostream>
#include <ctime>
#include <math.h>
#include <windows.h>
#define g 9.81
#define m2p 50.0


using namespace std;

template <class A>
A normD(A v1[], int size);

template <class A>
A dot(A v1[], A v2[]);

template <class A>
void convert2Uni(A v1[], int size);

template <class A>
void collisionCalc2D(A v10[], A v20[], A n[], A  m1, A m2, A e);


//computes the dot product of 2 vectors
template <class A>
A dot(A v1[], A v2[]){
	A sum = 0;
	for (int i = 0; i < 2; i++){
		sum += v1[i] * v2[i];
	}
	return sum;
}

// convert a vector into a unit vector
template <class A>
void convert2Uni(A v1[], int size){
	A mV1 = norm(v1, size);
	for (int i = 0; i < size; i++){
		v1[i] /= mV1;
	}
}

//computer the magnetude of a vector
template <class A>
A norm(A v1[], int size){
	switch (size){
	case 2:
		return sqrt(pow(v1[0], 2) + pow(v1[1], 2));
	case 3:
		return sqrt(pow(v1[0], 2) + pow(v1[1], 2) + pow(v1[2], 2));
	default:
		return 0;
	}
}

// set v10, v20 two velocity to new velocity after impact
// n - normal direction of the contact point
// m1, m2 - masses of the two bodies
// e - coefficient of restitution 
template <class A>
void collisionCalc2D(A v10[], A v20[], A n[], A  m1, A m2, A e){
	//univector for the t-axis
	A t[2] = { -n[1], n[0] };

	//velocity in the t and n axis with dot product
	A v1t0 = dot(v10, t);
	A v1n0 = dot(v10, n);

	A v2t0 = dot(v20, t);
	A v2n0 = dot(v20, n);

	//calculate the final velocity in the n axis
	A v1n = ((m1 - m2)*v1n0 + m2*(1 - e)*v2n0) / (m1 + m2);
	A v2n = v1n + e*(v1n0 - v2n0);
	
	//vt0 = vtf
	v10[0] = (v1t0 + v1n)*(t[0] + n[0]);
	v10[1] = (v1t0 + v1n)*(t[1] + n[1]);

	v20[0] = (v2t0 + v2n)*(t[0] + n[0]);
	v20[1] = (v2t0 + v2n)*(t[1] + n[1]);

}