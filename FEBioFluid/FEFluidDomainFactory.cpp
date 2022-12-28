/*This file is part of the FEBio source code and is licensed under the MIT license
listed below.

See Copyright-FEBio.txt for details.

Copyright (c) 2021 University of Utah, The Trustees of Columbia University in
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
#include "FEFluidDomainFactory.h"
#include "FEFluid.h"
#include "FEFluidDomain.h"
#include <FECore/FESolidDomain.h>
#include <FECore/FEDomain2D.h>

//-----------------------------------------------------------------------------
FEDomain* FEFluidDomainFactory::CreateDomain(const FE_Element_Spec& spec, FEMesh* pm, FEMaterial* pmat)
{
	FEModel* pfem = pmat->GetFEModel();
	FE_Element_Class eclass = spec.eclass;
	FE_Element_Shape eshape = spec.eshape;
	const char* sztype = 0;

	FEDomain* pd = nullptr;
	if (dynamic_cast<FEFluid*>(pmat))
	{
		// fluid elements
		if      (eclass==FE_ELEM_SOLID) pd = fecore_new<FESolidDomain>("fluid-3D", pfem);
        else if (eclass==FE_ELEM_2D   ) pd = fecore_new<FEDomain2D   >("fluid-2D", pfem);
		else return 0;
	}
	if (pd) pd->SetMaterial(pmat);
	return pd;
}
