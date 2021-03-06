/*
 *  Open BEAGLE: A Generic Evolutionary Computation Framework in C++
 *  Copyright (C) 2001-2010 by Christian Gagne and Marc Parizeau
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, version 3 of the License.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License and GNU General Public License for
 *  more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License and GNU General Public License along with this library.
 *  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Contact:
 *  Christian Gagne
 *  Laboratoire de vision et systemes numeriques
 *  Departement de genie electrique et de genie informatique
 *  Universite Laval, Quebec (Quebec), Canada  G1V 0A6
 *  http://vision.gel.ulaval.ca/~cgagne
 *  christian.gagne@gel.ulaval.ca
 *
 */

/*!
 *  \file   Beagle/EC/MuPlusLambdaOp.hpp
 *  \brief  Definition of the class MuPlusLambdaOp.
 *  \author Christian Gagne
 *  \author Marc Parizeau
 *  $Revision: 1.14 $
 *  $Date: 2007/08/17 18:09:13 $
 */


#ifndef Beagle_EC_MuPlusLambdaOp_hpp
#define Beagle_EC_MuPlusLambdaOp_hpp

#include "Beagle/Core.hpp"


namespace Beagle
{

namespace EC
{

/*!
 *  \class MuPlusLambdaOp Beagle/EC/MuPlusLambdaOp.hpp "Beagle/EC/MuPlusLambdaOp.hpp"
 *  \brief Mu plus lambda (Mu+Lambda) replacement strategy operator class.
 *  \ingroup EC
 *  \ingroup Op
 *
 *  A (Mu+Lambda) operator generates Lambda children individuals from a population of Mu parents
 *  (usually where Lambda > Mu). From the Mu parents and the Lambda individual, it keeps the Mu best
 *  individuals to constitute the new generation.
 */
class MuPlusLambdaOp : public Beagle::ReplacementStrategyOp
{

public:

	//! MuPlusLambdaOp allocator type.
	typedef Beagle::AllocatorT<MuPlusLambdaOp,Beagle::ReplacementStrategyOp::Alloc>
	Alloc;
	//! MuPlusLambdaOp handle type.
	typedef Beagle::PointerT<MuPlusLambdaOp,Beagle::ReplacementStrategyOp::Handle>
	Handle;
	//! MuPlusLambdaOp bag type.
	typedef Beagle::ContainerT<MuPlusLambdaOp,Beagle::ReplacementStrategyOp::Bag>
	Bag;

	explicit MuPlusLambdaOp(std::string inLMRatioName="ec.mulambda.ratio",
	                        std::string inName="MuPlusLambdaOp");
	virtual ~MuPlusLambdaOp()
	{ }

	virtual void registerParams(Beagle::System& ioSystem);
	virtual void operate(Beagle::Deme& ioDeme, Beagle::Context& ioContext);
	virtual void readWithSystem(PACC::XML::ConstIterator inIter, Beagle::System& ioSystem);
	virtual void write(PACC::XML::Streamer& ioStreamer, bool inIndent=true) const;

protected:

	Beagle::Float::Handle mLMRatio;         //!< (Lambda / Mu) ratio to use for replacement operator.
	std::string           mLMRatioName;     //!< (Lambda / Mu) ratio parameter name used in register.

};

}

}

#endif // Beagle_EC_MuPlusLambdaOp_hpp
