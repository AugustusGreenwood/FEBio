#pragma once

#include "FECore/FENewtonSolver.h"
#include "FEStiffnessMatrix.h"
#include "FECore/FETypes.h"

//-----------------------------------------------------------------------------
//! The FESolidSolver class solves large deformation solid mechanics problems
//! It can deal with quasi-static and dynamic problems
//! 
class FESolidSolver : public FENewtonSolver
{
public:
	//! constructor
	FESolidSolver(FEModel* pfem);

	//! destructor
	virtual ~FESolidSolver();

	//! Clean up
	virtual void Clean();

	//! serialize data to/from dump file
	void Serialize(DumpFile& ar);

	//! Initializes data structures
	bool Init();

	//! solves a single time step
	bool SolveStep(double time);

	//! Initialize linear equation system
	bool InitEquations();

public:
	//! assemble the element residual into the global residual
	//! \todo This was implemented for nodal forces
	void AssembleResidual(int node, int dof, double f, vector<double>& R);

	//! adjust the residual matrix for prescribed displacements
	void AssembleStiffness(vector<int>& en, vector<int>& elm, matrix& ke);

	//! assemble global stiffness matrix \todo this is only used by rigid joints
	void AssembleStiffness(vector<int>& elm, matrix& ke);

public:
	//{ --- evaluation and update ---
		//! Perform an update
		void Update(vector<double>& ui);

		//! Evaluate system, i.e. calculate residual
		void Evaluate(vector<double>& R) { Residual(R); }
	//}

	//{ --- Solution functions ---

		//! prepares the data for the first QN iteration
		virtual void PrepStep(double time);

		//! Performs a Newton-Raphson iteration
		virtual bool Quasin(double time);

		//! update nodal positions, velocities, accelerations, etc.
		virtual void UpdateKinematics(vector<double>& ui);

		//! update rigid body kinematics for dynamic problems
		void UpdateRigidKinematics();

		//! Update Stresses
		void UpdateStresses();

		//! Update rigid body data
		void UpdateRigidBodies(vector<double>& ui);

		//! update contact data
		virtual void UpdateContact();

		//! update constraint data
		virtual void UpdateConstraints();

		//! Lagrangian augmentation
		bool Augment();
	//}

	//{ --- Stiffness matrix routines ---
		//! return pointer to stiffness matrix
		FEStiffnessMatrix* GetStiffnessMatrix() { return m_pK; }

		//! recalculates the shape of the stiffness matrix
		bool CreateStiffness(bool breset);

		//! calculates the global stiffness matrix
		virtual bool StiffnessMatrix(const FETimePoint& tp);

		//! contact stiffness
		void ContactStiffness();

		//! reform the stiffness matrix
		bool ReformStiffness();

		//! calculate the rigid stiffnes matrices
		void RigidStiffness(vector<int>& en, vector<int>& elm, matrix& ke);

		//! calculates stiffness contributon of nonlinear constraints
		void NonLinearConstraintStiffness(const FETimePoint& tp);
	//}

	//{ --- Residual routines ---

		//! Calculates concentrated nodal forces
		void NodalForces(vector<double>& F, const FETimePoint& tp);

		//! Calculate inertial forces for dynamic problems
		void InertialForces(FEGlobalVector& R);

		//! Calculate the contact forces
		void ContactForces(FEGlobalVector& R);

		//! Calculates residual
		virtual bool Residual(vector<double>& R);

		//! Calculate nonlinear constraint forces
		void NonLinearConstraintForces(FEGlobalVector& R, const FETimePoint& tp);
	//}

public:
	// convergence tolerances
	double	m_Rtol;			//!< residual tolerance
	double	m_Dtol;			//!< displacement tolerance
	double	m_Etol;			//!< energy tolerance
	double	m_Rmin;			//!< min residual value

	// strategy parameters
	bool	m_bdivreform;	//!< reform when diverging
	bool	m_bdoreforms;	//!< do reformations

	// equation numbers
	int		m_nreq;			//!< start of rigid body equations

	// Newmark parameters (for dynamic analyses)
	double	m_beta;			//!< Newmark parameter beta (displacement integration)
	double	m_gamma;		//!< Newmark parameter gamme (velocity integration)

public:
	vector<double> m_Fn;	//!< concentrated nodal force vector
	vector<double> m_Fr;	//!< nodal reaction forces
	vector<double> m_Ui;	//!< Total displacement vector for iteration
	vector<double> m_Ut;	//!< Total dispalcement vector at time t (incl all previous timesteps)
	vector<double> m_Fd;	//!< residual correction due to prescribed displacements

	// matrix reshape flag
	bool	m_breshape;		//!< Matrix reshape flag

public:
	LinearSolver*		m_plinsolve;	//!< the linear solver

	// global stiffness matrix
	FEStiffnessMatrix*	m_pK;		//!< global stiffness matrix
	int					m_neq;		//!< number of equations

	bool		m_baugment;		//!< augmentation flag

	bool	m_bnew_update;	//!< use new rigid body update algorithm

	// declare the parameter list
	DECLARE_PARAMETER_LIST();
};
