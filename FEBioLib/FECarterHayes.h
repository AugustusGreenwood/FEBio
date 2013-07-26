/*
 *  FECarterHayesNew.h
 *  FEBioXCode
 *
 *  Created by Gerard Ateshian on 5/24/13.
 *  Copyright 2013 Columbia University. All rights reserved.
 *
 */

#pragma once
#include <FECore/FEElasticMaterial.h>
#include "FEBioMix/FEMultiphasic.h"

//-----------------------------------------------------------------------------
//! This is a neo-Hookean material whose Young's modulus is evaluated from the density
//! according to the power-law relation proposed by Carter and Hayes for trabecular bone

class FECarterHayes : public FEElasticMaterial
{
public:
	FECarterHayes() {}
	
public:
	double	m_c;	//!< c coefficient for calculation of Young's modulus
	double	m_g;	//!< gamma exponent for calculation of Young's modulus
	double	m_v;	//!< prescribed Poisson's ratio
	int		m_sbm;	//!< global id of solid-bound molecule
	int		m_lsbm;	//!< local id of solid-bound molecule
	
public:
	//! calculate strain energy density at material point
	double StrainEnergy(FEMaterialPoint& pt);
	
	//! calculate stress at material point
	mat3ds Stress(FEMaterialPoint& pt);
	
	//! calculate tangent stiffness at material point
	tens4ds Tangent(FEMaterialPoint& pt);
	
	//! calculate tangent of strain energy density with mass density
	double Tangent_SE_Density(FEMaterialPoint& pt);
	
	//! calculate tangent of stress with mass density
	mat3ds Tangent_Stress_Density(FEMaterialPoint& pt);
	
	//! data initialization and checking
	void Init();
	
	//! return Young's modulus
	double YoungModulus(double rhor) { return m_c*pow(rhor, m_g);}
	
	//! return bulk modulus
	double BulkModulus() { return YoungModulus(Density())/(3.0*(1.0 - 2.0*m_v));}
	
	// declare as registered
	DECLARE_REGISTERED(FECarterHayes);
	
	// declare the parameter list
	DECLARE_PARAMETER_LIST();
};
