#pragma once
#include <FECore/LinearSolver.h>
#include "CompactUnSymmMatrix.h"

//-----------------------------------------------------------------------------
// This class implements the HYPRE GMRES solver
class HypreGMRESsolver : public LinearSolver
{
	class Implementation;

public:
	HypreGMRESsolver(FEModel* fem);
	~HypreGMRESsolver();

	void SetPrintLevel(int n);

	void SetMaxIterations(int n);

	void SetConvergencTolerance(double tol);

public:
	// allocate storage
	bool PreProcess();

	//! Factor the matrix (for iterative solvers, this can be used for creating pre-conditioner)
	bool Factor();

	//! Calculate the solution of RHS b and store solution in x
	bool BackSolve(double* x, double* b);

	//! Return a sparse matrix compatible with this solver
	SparseMatrix* CreateSparseMatrix(Matrix_Type ntype);

	//! set the sparse matrix
	bool SetSparseMatrix(SparseMatrix* A) override;

private:
	Implementation*	imp;
};
