#pragma once
#include "FECore/FEPlotData.h"
#include "FEBioLib/FEElasticShellDomain.h"
#include "FEBioLib/FEElasticSolidDomain.h"
#include "FEBioLib/FELinearSolidDomain.h"

//=============================================================================
// The following classes define data fields for domains. 
//=============================================================================

//-----------------------------------------------------------------------------
//! Element stresses
class FEPlotElementStress : public FEDomainData
{
public:
	FEPlotElementStress(FEModel* pfem) : FEDomainData(PLT_MAT3FS, FMT_ITEM){}
	bool Save(FEDomain& dom, vector<float>& a);

protected:
	bool WriteSolidStress(FEElasticSolidDomain& d, vector<float>& a);
	bool WriteShellStress(FEElasticShellDomain& d, vector<float>& a);

	bool WriteLinearSolidStress(FELinearSolidDomain& d, vector<float>& a);
};

//-----------------------------------------------------------------------------
//! Relative volume
class FEPlotRelativeVolume : public FEDomainData
	{
	public:
		FEPlotRelativeVolume(FEModel* pfem) : FEDomainData(PLT_FLOAT, FMT_ITEM){}
		bool Save(FEDomain& dom, vector<float>& a);
	};

//-----------------------------------------------------------------------------
//! Actual fluid pressure
class FEPlotActualFluidPressure : public FEDomainData
	{
	public:
		FEPlotActualFluidPressure(FEModel* pfem) : FEDomainData(PLT_FLOAT, FMT_ITEM){}
		bool Save(FEDomain& dom, vector<float>& a);
	};

//-----------------------------------------------------------------------------
//! Fluid flux
class FEPlotFluidFlux : public FEDomainData
{
public:
	FEPlotFluidFlux(FEModel* pfem) : FEDomainData(PLT_VEC3F, FMT_ITEM){}
	bool Save(FEDomain& dom, vector<float>& a);
};

//-----------------------------------------------------------------------------
//! Nodal Fluid flux
class FEPlotNodalFluidFlux : public FEDomainData
{
public:
	FEPlotNodalFluidFlux(FEModel* pfem) : FEDomainData(PLT_VEC3F, FMT_MULT){}
	bool Save(FEDomain& dom, vector<float>& a);
};

//-----------------------------------------------------------------------------
//! Actual solute concentration
class FEPlotActualSoluteConcentration : public FEDomainData
	{
	public:
		FEPlotActualSoluteConcentration(FEModel* pfem) : FEDomainData(PLT_FLOAT, FMT_ITEM){}
		bool Save(FEDomain& dom, vector<float>& a);
	};

//-----------------------------------------------------------------------------
//! Base class for solute concentration variables
class FEPlotActualSolConcentration_ : public FEDomainData
{
public:
	FEPlotActualSolConcentration_(FEModel* pfem, int nsol) : FEDomainData(PLT_FLOAT, FMT_ITEM), m_nsol(nsol) {}
	bool Save(FEDomain& dom, vector<float>& a);
private:
	int	m_nsol;
};

//-----------------------------------------------------------------------------
// template class for instantiating solute concentration classes
template<int SOL> class FEPlotActualSolConcentrationT : public FEPlotActualSolConcentration_
{
public:
	FEPlotActualSolConcentrationT(FEModel* pfem) : FEPlotActualSolConcentration_(pfem, SOL) {}
};

//-----------------------------------------------------------------------------
//! Solute flux (for biphasic solute problems)
class FEPlotSoluteFlux : public FEDomainData
{
public:
	FEPlotSoluteFlux(FEModel* pfem) : FEDomainData(PLT_VEC3F, FMT_ITEM){}
	bool Save(FEDomain& dom, vector<float>& a);
};

//-----------------------------------------------------------------------------
//! Base class for solute flux variables
class FEPlotSolFlux_ : public FEDomainData
{
public:
	FEPlotSolFlux_(FEModel* pfem, int nsol) : FEDomainData(PLT_VEC3F, FMT_ITEM), m_nsol(nsol) {}
	bool Save(FEDomain& dom, vector<float>& a);
private:
	int	m_nsol;
};

//-----------------------------------------------------------------------------
// template class for instantiating solute flux classes
template<int SOL> class FEPlotSolFluxT : public FEPlotSolFlux_
{
public:
	FEPlotSolFluxT(FEModel* pfem) : FEPlotSolFlux_(pfem, SOL){}
};

//-----------------------------------------------------------------------------
//! Electric potential
class FEPlotElectricPotential : public FEDomainData
{
public:
	FEPlotElectricPotential(FEModel* pfem) : FEDomainData(PLT_FLOAT, FMT_ITEM){}
	bool Save(FEDomain& dom, vector<float>& a);
};

//-----------------------------------------------------------------------------
//! Current density
class FEPlotCurrentDensity : public FEDomainData
{
public:
	FEPlotCurrentDensity(FEModel* pfem) : FEDomainData(PLT_VEC3F, FMT_ITEM){}
	bool Save(FEDomain& dom, vector<float>& a);
};

//-----------------------------------------------------------------------------
//! Fixed charge density
class FEPlotFixedChargeDensity : public FEDomainData
{
public:
	FEPlotFixedChargeDensity(FEModel* pfem) : FEDomainData(PLT_FLOAT, FMT_ITEM){}
	bool Save(FEDomain& dom, vector<float>& a);
};

//-----------------------------------------------------------------------------
//! Material fibers
class FEPlotFiberVector : public FEDomainData
{
public:
	FEPlotFiberVector(FEModel* pfem) : FEDomainData(PLT_VEC3F, FMT_ITEM){}
	bool Save(FEDomain& dom, vector<float>& a);
};

//-----------------------------------------------------------------------------
//! Shell thicknesses
class FEPlotShellThickness : public FEDomainData
{
public:
	FEPlotShellThickness(FEModel* pfem) : FEDomainData(PLT_FLOAT, FMT_MULT){}
	bool Save(FEDomain& dom, vector<float>& a);
};


//-----------------------------------------------------------------------------
//! Nodal effective fluid pressures
class FEPlotEffectiveFluidPressure : public FEDomainData
{
public:
	FEPlotEffectiveFluidPressure(FEModel* pfem) : FEDomainData(PLT_FLOAT, FMT_NODE){}
	bool Save(FEDomain& m, vector<float>& a);
};

//-----------------------------------------------------------------------------
//! Nodal effective solute concentrations (for biphasic-solute problems)
class FEPlotEffectiveSoluteConcentration : public FEDomainData
{
public:
	FEPlotEffectiveSoluteConcentration(FEModel* pfem) : FEDomainData(PLT_FLOAT, FMT_NODE){}
	bool Save(FEDomain& m, vector<float>& a);
};

//-----------------------------------------------------------------------------
//! Base class for nodal effective solute concentrations
class FEPlotEffectiveSolConcentration_ : public FEDomainData
{
public:
	FEPlotEffectiveSolConcentration_(FEModel* pfem, int nsol) : FEDomainData(PLT_FLOAT, FMT_NODE), m_nsol(nsol) {}
	bool Save(FEDomain& m, vector<float>& a);
private:
	int m_nsol;
};

//-----------------------------------------------------------------------------
//! template class for instantiating nodal effective solute concentrations
template<int SOL> class FEPlotEffectiveSolConcentrationT : public FEPlotEffectiveSolConcentration_
{
public:
	FEPlotEffectiveSolConcentrationT(FEModel* pfem) : FEPlotEffectiveSolConcentration_(pfem, SOL) {}
};

//-----------------------------------------------------------------------------
//! Damage reduction factor
class FEPlotDamage : public FEDomainData
{
public:
	FEPlotDamage(FEModel* pfem) : FEDomainData(PLT_FLOAT, FMT_ITEM){}
	bool Save(FEDomain& m, vector<float>& a);
};

//-----------------------------------------------------------------------------
//! Mixture volume fraction
class FEPlotMixtureVolumeFraction : public FEDomainData
{
public:
	FEPlotMixtureVolumeFraction(FEModel* pfem) : FEDomainData(PLT_FLOAT, FMT_ITEM){}
	bool Save(FEDomain& m, vector<float>& a);
};

//-----------------------------------------------------------------------------
//! Receptor-ligand complex concentration
class FEPlotReceptorLigandConcentration : public FEDomainData
{
public:
	FEPlotReceptorLigandConcentration(FEModel* pfem) : FEDomainData(PLT_FLOAT, FMT_ITEM){}
	bool Save(FEDomain& dom, vector<float>& a);
};
