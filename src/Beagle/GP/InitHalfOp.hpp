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
 *  \file   beagle/GP/InitHalfOp.hpp
 *  \brief  Definition of the class GP::InitHalfOp.
 *  \author Christian Gagne
 *  \author Marc Parizeau
 *  $Revision: 1.15 $
 *  $Date: 2007/08/08 19:26:35 $
 */

#ifndef Beagle_GP_InitHalfOp_hpp
#define Beagle_GP_InitHalfOp_hpp

#include <string>

#include "Beagle/config.hpp"
#include "Beagle/macros.hpp"
#include "Beagle/Core/Object.hpp"
#include "Beagle/Core/AllocatorT.hpp"
#include "Beagle/Core/PointerT.hpp"
#include "Beagle/Core/ContainerT.hpp"
#include "Beagle/EC/InitializationOp.hpp"
#include "Beagle/GP/InitFullOp.hpp"
#include "Beagle/GP/InitGrowOp.hpp"


namespace Beagle
{
namespace GP
{

/*!
 *  \class InitHalfOp beagle/GP/InitHalfOp.hpp "beagle/GP/InitHalfOp.hpp"
 *  \brief GP trees "half-and-half" initialization operator class.
 *  \ingroup GPF
 *  \ingroup GPOp
 *  \ingroup GPPop
 */
class InitHalfOp : public GP::InitializationOp
{

public:

	//! GP::InitHalfOp allocator type.
	typedef AllocatorT<InitHalfOp,InitializationOp::Alloc>
	Alloc;
	//! GP::InitHalfOp handle type.
	typedef PointerT<InitHalfOp,InitializationOp::Handle>
	Handle;
	//! GP::InitGrowOp bag type.
	typedef ContainerT<InitHalfOp,InitializationOp::Bag>
	Bag;

	explicit InitHalfOp(std::string inReproProbaName="ec.repro.prob",
	                    std::string inName="GP-InitHalfOp");
	virtual ~InitHalfOp()
	{ }

	virtual void registerParams(Beagle::System& ioSystem);
	virtual unsigned int initTree(GP::Tree &outTree,
	                              unsigned int inMinDepth,
	                              unsigned int inMaxDepth,
	                              GP::Context &ioContext) const;

protected:

	GP::InitFullOp mInitFullOp;  //!< Full initialization operator.
	GP::InitGrowOp mInitGrowOp;  //!< Grow initialization operator.

};

}
}

#endif // Beagle_GP_InitHalfOp_hpp
