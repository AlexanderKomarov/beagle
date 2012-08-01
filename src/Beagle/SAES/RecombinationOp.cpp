/*
 *  Open BEAGLE
 *  Copyright (C) 2001-2007 by Christian Gagne and Marc Parizeau
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Contact:
 *  Laboratoire de Vision et Systemes Numeriques
 *  Departement de genie electrique et de genie informatique
 *  Universite Laval, Quebec, Canada, G1K 7P4
 *  http://vision.gel.ulaval.ca
 *
 */

/*!
 *  \file   Beagle/SAES/RecombinationOp.cpp
 *  \brief  Source code of class SAES::RecombinationOp.
 *  \author Christian Gagne
 *  $Revision: 1.5 $
 *  $Date: 2007/08/17 18:09:10 $
 */

#include "Beagle/SAES.hpp"

#include <cfloat>
#include <cmath>
#include <float.h>
#include <algorithm>
#include <string>

using namespace Beagle;


/*!
 *  \brief Construct a SA-ES recombination by averaging operator.
 *  \param inRecombPbName Recombination individual probability name.
 *  \param inNumberRecombName Number of individuals recombined parameter name.
 *  \param inName Name of the operator.
 */
SAES::RecombinationOp::RecombinationOp(std::string inRecombPbName,
        std::string inNumberRecombName,
        std::string inName) :
		EC::RecombinationOp(inRecombPbName, inNumberRecombName, inName)
{ }


/*!
 *  \brief Recombine individuals by averaging to generate a new individual.
 *  \param inIndivPool Parents being recombined.
 *  \param ioContext Evolutionary context.
 *  \return Children generated by recombination.
 */
Individual::Handle SAES::RecombinationOp::recombine(Individual::Bag& inIndivPool,
        Context& ioContext)
{
	Beagle_StackTraceBeginM();

	// Recombine parents to generate new individual.
	const Factory& lFactory = ioContext.getSystem().getFactory();
	Individual::Alloc::Handle lIndivAlloc =
	    castHandleT<Individual::Alloc>(lFactory.getConceptAllocator("Individual"));
	Genotype::Alloc::Handle lGenotypeAlloc =
		castHandleT<Genotype::Alloc>(lFactory.getConceptAllocator("Genotype"));
	Individual::Handle lChildIndiv = castHandleT<Individual>(lIndivAlloc->allocate());
	std::vector< std::vector<unsigned int> > lCountGenoSum;
	for(unsigned int i=0; i<inIndivPool.size(); ++i) {
		const unsigned int lPoolISize = inIndivPool[i]->size();
		const unsigned int lChildSize = lChildIndiv->size();
		if(lPoolISize > lChildSize) {
			lCountGenoSum.resize(lPoolISize);
			lChildIndiv->resize(lPoolISize);
			for(unsigned int j=lChildSize; j<lPoolISize; ++j) {
				(*lChildIndiv)[j] = castHandleT<Genotype>(lGenotypeAlloc->allocate());
			}
		}
		for(unsigned int j=0; j<lPoolISize; ++j) {
			SAES::PairVector::Handle lChildGenoJ = castHandleT<SAES::PairVector>((*lChildIndiv)[j]);
			SAES::PairVector::Handle lPoolIGenoJ = castHandleT<SAES::PairVector>((*inIndivPool[i])[j]);
			const unsigned int lPoolIGenoJSize = lPoolIGenoJ->size();
			if(lPoolIGenoJSize > lChildGenoJ->size()) {
				lChildGenoJ->resize(lPoolIGenoJSize,0.0);
				lCountGenoSum[j].resize(lPoolIGenoJSize,0);
			}
			for(unsigned int k=0; k<lPoolIGenoJSize; ++k) {
				(*lChildGenoJ)[k].mValue += (*lPoolIGenoJ)[k].mValue;
				(*lChildGenoJ)[k].mStrategy += (*lPoolIGenoJ)[k].mStrategy;
				++lCountGenoSum[j][k];
			}

		}
	}
	for(unsigned int i=0; i<lChildIndiv->size(); ++i) {
		SAES::PairVector::Handle lChildGenoI = castHandleT<SAES::PairVector>((*lChildIndiv)[i]);
		for(unsigned int j=0; j<lChildGenoI->size(); ++j) {
			(*lChildGenoI)[j].mValue /= double(lCountGenoSum[i][j]);
			(*lChildGenoI)[j].mStrategy /= double(lCountGenoSum[i][j]);
		}
	}

	Beagle_LogDebugM(ioContext.getSystem().getLogger(), *lChildIndiv);

	return lChildIndiv;
	Beagle_StackTraceEndM();
}