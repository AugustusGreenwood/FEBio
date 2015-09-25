#include "stdafx.h"
#include "BFGSSolver.h"
#include "FESolver.h"

//-----------------------------------------------------------------------------
// BFGSSolver
//-----------------------------------------------------------------------------

BFGSSolver::BFGSSolver()
{
	m_maxups = 10;
	m_maxref = 15;
	m_cmax   = 1e5;

	// pointer to linear solver
	m_plinsolve = 0;

	// pointer to non-linear system
	m_pNLS = 0;
}

//-----------------------------------------------------------------------------
// Initialization method
void BFGSSolver::Init(int neq, FESolver* pNLS, LinearSolver* pls)
{
	// allocate storage for BFGS update vectors
	m_V.resize(m_maxups, neq);
	m_W.resize(m_maxups, neq);

	m_D.resize(neq);
	m_G.resize(neq);
	m_H.resize(neq);

	m_ui.assign(neq, 0);
	m_R0.assign(neq, 0);
	m_R1.assign(neq, 0);

	m_neq = neq;
	m_nups = 0;

	m_plinsolve = pls;

	assert(pNLS);
	m_pNLS = pNLS;
}

//-----------------------------------------------------------------------------
//! This function performs a BFGS stiffness update.
//! The last line search step is input to this function.
//! This function performs the update assuming the stiffness matrix
//! is positive definite. In the case that this is not the case
//! the function returns false. The function also returns false if 
//! the condition number is too big. A too big condition number might
//! be an indication of an ill-conditioned matrix and the update should
//! not be performed.

bool BFGSSolver::Update(double s, vector<double>& ui, vector<double>& R0, vector<double>& R1)
{
	int i;
	double dg, dh,dgi, c, r;
	double *vn, *wn;

	int neq = ui.size();

	// calculate the BFGS update vectors
	for (i=0; i<neq; ++i)	
	{
		m_D[i] = s*ui[i];
		m_G[i] = R0[i] - R1[i];
		m_H[i] = R0[i]*s;
	}

	dg = m_D*m_G;
	dh = m_D*m_H;
	dgi = 1.0 / dg;
	r = dg/dh;

	// check to see if this is still a pos definite update
//	if (r <= 0) 
//	{
//		return false;
//	}

	// calculate the condition number
//	c = sqrt(r);
	c = sqrt(fabs(r));

	// make sure c is less than the the maximum.
	if (c > m_cmax) return false;

	vn = m_V[m_nups];
	wn = m_W[m_nups];

	// TODO: There might be a bug here. Check signs!
	for (i=0; i<neq; ++i)	
	{
		vn[i] = -m_H[i]*c - m_G[i];
		wn[i] = m_D[i]*dgi;
	}

	// increment update counter
	++m_nups;

	return true;
}

//-----------------------------------------------------------------------------
// This function solves a system of equations using the BFGS update vectors
// The variable m_nups keeps track of how many updates have been made so far.
// 

void BFGSSolver::SolveEquations(vector<double>& x, vector<double>& b)
{
	int i, j;
	double *vi, *wi, vr, wr;

	// get the nr of equations
	int neq = x.size();

	// make sure we need to do work
	if (neq==0) return;

	// create temporary storage
	static vector<double> tmp;
	tmp = b;

	// loop over all update vectors
	for (i=m_nups-1; i>=0; --i)
	{
		vi = m_V[i];
		wi = m_W[i];

		wr = 0;
		for (j=0; j<neq; j++) wr += wi[j]*tmp[j];

		for (j=0; j<neq; j++) tmp[j] += vi[j]*wr;
	}

	// perform a backsubstitution
	m_plinsolve->BackSolve(x, tmp);

	// loop again over all update vectors
	for (i=0; i<m_nups; ++i)
	{
		vi = m_V[i];
		wi = m_W[i];

		vr = 0;
		for (j=0; j<neq; ++j) vr += vi[j]*x[j];

		for (j=0; j<neq; ++j) x[j] += wi[j]*vr;
	}
}
