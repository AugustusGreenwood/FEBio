/*This file is part of the FEBio source code and is licensed under the MIT license
listed below.

See Copyright-FEBio.txt for details.

Copyright (c) 2020 University of Utah, The Trustees of Columbia University in 
the City of New York, and others.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/
#include "stdafx.h"
#include "FEFluidStressCriterion.h"
#include "FEFluid.h"
#include <FECore/FEElementList.h>

BEGIN_FECORE_CLASS(FEFluidStressCriterion, FEMeshAdaptorCriterion)
END_FECORE_CLASS();

FEFluidStressCriterion::FEFluidStressCriterion(FEModel* fem) : FEMeshAdaptorCriterion(fem)
{
}

bool FEFluidStressCriterion::GetElementValue(FEElement& el, double& elemVal)
{
	double v = 0.0;
	int nint = el.GaussPoints();
	for (int n = 0; n < nint; ++n)
	{
		FEMaterialPoint* mp = el.GetMaterialPoint(n);
		FEFluidMaterialPoint* fp = mp->ExtractData<FEFluidMaterialPoint>();
		if (fp == nullptr) return false;

		mat3ds& s = fp->m_sf;
		v += s.max_shear();
	}
	v /= (double)nint;

	elemVal = v;
	return true;
}


FEFluidStressErrorCriterion::FEFluidStressErrorCriterion(FEModel* fem) : FEDomainErrorCriterion(fem)
{
}

double FEFluidStressErrorCriterion::GetMaterialPointValue(FEMaterialPoint& mp)
{
	FEFluidMaterialPoint& fp = *mp.ExtractData<FEFluidMaterialPoint>();
	mat3ds s = fp.m_sf;
	double v = s.max_shear();
	return v;
}
