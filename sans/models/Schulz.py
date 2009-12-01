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
 	         DO NOT MODIFY THIS FILE, MODIFY ../c_extensions/schulz.h
 	         AND RE-RUN THE GENERATOR SCRIPT

"""

from sans.models.BaseComponent import BaseComponent
from sans_extension.c_models import CSchulz
import copy    
    
class Schulz(CSchulz, BaseComponent):
    """ Class that evaluates a Schulz model. 
    	This file was auto-generated from ../c_extensions/schulz.h.
    	Refer to that file and the structure it contains
    	for details of the model.
    	List of default parameters:
         scale           = 1.0 
         sigma           = 1.0 
         center          = 0.0 

    """
        
    def __init__(self):
        """ Initialization """
        
        # Initialize BaseComponent first, then sphere
        BaseComponent.__init__(self)
        CSchulz.__init__(self)
        
        ## Name of the model
        self.name = "Schulz"
        ## Model description
        self.description =""" f(x)=scale * math.pow(z+1, z+1)*math.pow((R), z)*
		math.exp(-R*(z+1))/(center*gamma(z+1)
		z= math.pow[(1/(sigma/center),2]-1"""
       
		## Parameter details [units, min, max]
        self.details = {}
        self.details['scale'] = ['', None, None]
        self.details['sigma'] = ['', None, None]
        self.details['center'] = ['', None, None]

		## fittable parameters
        self.fixed=[]
        
        ## parameters with orientation
        self.orientation_params =[]
   
    def clone(self):
        """ Return a identical copy of self """
        return self._clone(Schulz())   
   
    def run(self, x = 0.0):
        """ Evaluate the model
            @param x: input q, or [q,phi]
            @return: scattering function P(q)
        """
        
        return CSchulz.run(self, x)
   
    def runXY(self, x = 0.0):
        """ Evaluate the model in cartesian coordinates
            @param x: input q, or [qx, qy]
            @return: scattering function P(q)
        """
        
        return CSchulz.runXY(self, x)
        
    def evalDistribition(self, x = []):
        """ Evaluate the model in cartesian coordinates
            @param x: input q[], or [qx[], qy[]]
            @return: scattering function P(q[])
        """
        return CSchulz.evalDistribition(self, x)
        
    def calculate_ER(self):
        """ Calculate the effective radius for P(q)*S(q)
            @return: the value of the effective radius
        """       
        return CSchulz.calculate_ER(self)
        
    def set_dispersion(self, parameter, dispersion):
        """
            Set the dispersion object for a model parameter
            @param parameter: name of the parameter [string]
            @dispersion: dispersion object of type DispersionModel
        """
        return CSchulz.set_dispersion(self, parameter, dispersion.cdisp)
        
   
# End of file
