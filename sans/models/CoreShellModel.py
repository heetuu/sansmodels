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
 	         DO NOT MODIFY THIS FILE, MODIFY ..\c_extensions\core_shell.h
 	         AND RE-RUN THE GENERATOR SCRIPT

"""

from sans.models.BaseComponent import BaseComponent
from sans_extension.c_models import CCoreShellModel
import copy    
    
class CoreShellModel(CCoreShellModel, BaseComponent):
    """ Class that evaluates a CoreShellModel model. 
    	This file was auto-generated from ..\c_extensions\core_shell.h.
    	Refer to that file and the structure it contains
    	for details of the model.
    	List of default parameters:
         scale           = 1.0 
         radius          = 60.0 [A]
         thickness       = 10.0 [A]
         core_sld        = 1e-006 [1/A�]
         shell_sld       = 2e-006 [1/A�]
         solvent_sld     = 3e-006 [1/A�]
         background      = 0.0 [1/cm]

    """
        
    def __init__(self):
        """ Initialization """
        
        # Initialize BaseComponent first, then sphere
        BaseComponent.__init__(self)
        CCoreShellModel.__init__(self)
        
        ## Name of the model
        self.name = "CoreShellModel"
        ## Model description
        self.description ="""Form factor for a monodisperse spherical particle with particle
		with a core-shell structure:
		
		The form factor is normalized by the
		total particle volume.
		
		radius: core radius, thickness: shell thickness
		
		Ref: Guinier, A. and G. Fournet,
		John Wiley and Sons, New York, 1955."""
       
		## Parameter details [units, min, max]
        self.details = {}
        self.details['scale'] = ['', None, None]
        self.details['radius'] = ['[A]', None, None]
        self.details['thickness'] = ['[A]', None, None]
        self.details['core_sld'] = ['[1/A�]', None, None]
        self.details['shell_sld'] = ['[1/A�]', None, None]
        self.details['solvent_sld'] = ['[1/A�]', None, None]
        self.details['background'] = ['[1/cm]', None, None]

		## fittable parameters
        self.fixed=['thickness.width', 'radius.width']
        
        ## parameters with orientation
        self.orientation_params =[]
   
    def clone(self):
        """ Return a identical copy of self """
        return self._clone(CoreShellModel())   
   
    def run(self, x = 0.0):
        """ Evaluate the model
            @param x: input q, or [q,phi]
            @return: scattering function P(q)
        """
        
        return CCoreShellModel.run(self, x)
   
    def runXY(self, x = 0.0):
        """ Evaluate the model in cartesian coordinates
            @param x: input q, or [qx, qy]
            @return: scattering function P(q)
        """
        
        return CCoreShellModel.runXY(self, x)
        
    def set_dispersion(self, parameter, dispersion):
        """
            Set the dispersion object for a model parameter
            @param parameter: name of the parameter [string]
            @dispersion: dispersion object of type DispersionModel
        """
        return CCoreShellModel.set_dispersion(self, parameter, dispersion.cdisp)
        
   
# End of file
