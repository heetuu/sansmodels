#!/usr/bin/env python
"""
	This software was developed by the University of Tennessee as part of the
	Distributed Data Analysis of Neutron Scattering Experiments (DANSE)
	project funded by the US National Science Foundation.

	If you use DANSE applications to do scientific research that leads to
	publication, we ask that you acknowledge the use of the software with the
	following sentence:

	"This work benefited from DANSE software developed under NSF award DMR-0520547."

	copyright 2008, University of Tennessee
"""

""" Provide functionality for a C extension model

	WARNING: THIS FILE WAS GENERATED BY WRAPPERGENERATOR.PY
 	         DO NOT MODIFY THIS FILE, MODIFY C:\ECLPS\workspace\trunk\sansmodels\src\sans\models\c_extensions\DiamEllip.h
 	         AND RE-RUN THE GENERATOR SCRIPT

"""

from sans.models.BaseComponent import BaseComponent
from sans_extension.c_models import CDiamEllipFunc
import copy    
    
class DiamEllipFunc(CDiamEllipFunc, BaseComponent):
    """ Class that evaluates a DiamEllipFunc model. 
    	This file was auto-generated from C:\ECLPS\workspace\trunk\sansmodels\src\sans\models\c_extensions\DiamEllip.h.
    	Refer to that file and the structure it contains
    	for details of the model.
    	List of default parameters:
         radius_a        = 20.0 A
         radius_b        = 400.0 A

    """
        
    def __init__(self):
        """ Initialization """
        
        # Initialize BaseComponent first, then sphere
        BaseComponent.__init__(self)
        CDiamEllipFunc.__init__(self)
        
        ## Name of the model
        self.name = "DiamEllipFunc"
        ## Model description
        self.description ="""To calculate the 2nd virial coefficient for
		the non-spherical object, then find the
		radius of sphere that has this value of
		virial coefficient:
		radius_a = polar radius,
		radius_b = equatorial radius;
		radius_a > radius_b: Prolate spheroid,
		radius_a < radius_b: Oblate spheroid."""
       
		## Parameter details [units, min, max]
        self.details = {}
        self.details['radius_a'] = ['A', None, None]
        self.details['radius_b'] = ['A', None, None]

		## fittable parameters
        self.fixed=['radius_a.width', 'radius_b.width']
   
    def clone(self):
        """ Return a identical copy of self """
        return self._clone(DiamEllipFunc())   
   
    def run(self, x = 0.0):
        """ Evaluate the model
            @param x: input q, or [q,phi]
            @return: scattering function P(q)
        """
        
        return CDiamEllipFunc.run(self, x)
   
    def runXY(self, x = 0.0):
        """ Evaluate the model in cartesian coordinates
            @param x: input q, or [qx, qy]
            @return: scattering function P(q)
        """
        
        return CDiamEllipFunc.runXY(self, x)
        
    def set_dispersion(self, parameter, dispersion):
        """
            Set the dispersion object for a model parameter
            @param parameter: name of the parameter [string]
            @dispersion: dispersion object of type DispersionModel
        """
        return CDiamEllipFunc.set_dispersion(self, parameter, dispersion.cdisp)
        
   
# End of file
