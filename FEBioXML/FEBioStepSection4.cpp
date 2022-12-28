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
#include "FEBioStepSection4.h"
#include "FEBioControlSection4.h"
#include "FEBioInitialSection3.h"
#include "FEBioBoundarySection3.h"
#include "FEBioLoadsSection.h"
#include "FEBioConstraintsSection.h"
#include "FEBioContactSection.h"
#include "FEBioRigidSection4.h"
#include "FEBioMeshAdaptorSection.h"

//-----------------------------------------------------------------------------
FEBioStepSection4::FEBioStepSection4(FEFileImport* pim) : FEFileSection(pim) {}

//-----------------------------------------------------------------------------
void FEBioStepSection4::Parse(XMLTag& tag)
{
	// Build the file section map
	FEFileImport* imp = GetFileReader();
	FEFileSectionMap Map;
	Map["Control"    ] = new FEBioControlSection4(imp);
	Map["Initial"    ] = new FEBioInitialSection3(imp);
	Map["Boundary"   ] = new FEBioBoundarySection3(imp);
	Map["Loads"      ] = new FEBioLoadsSection3(imp);
	Map["Constraints"] = new FEBioConstraintsSection25(imp);
	Map["Contact"    ] = new FEBioContactSection25(imp);
	Map["Rigid"      ] = new FEBioRigidSection4(imp);
	Map["MeshAdaptor"] = new FEBioMeshAdaptorSection(imp);

	++tag;
	do
	{
		if (tag == "step")
		{
			// create next step
			GetBuilder()->NextStep();

			// parse the file sections
			Map.Parse(tag);
		}
		++tag;
	}
	while (!tag.isend());
}
