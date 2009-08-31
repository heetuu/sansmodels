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
 	         DO NOT MODIFY THIS FILE, MODIFY ..\c_extensions\stacked_disks.h
 	         AND RE-RUN THE GENERATOR SCRIPT

"""

from sans.models.BaseComponent import BaseComponent
from sans_extension.c_models import CStackedDisksModel
import copy    
    
class StackedDisksModel(CStackedDisksModel, BaseComponent):
    """ Class that evaluates a StackedDisksModel model. 
    	This file was auto-generated from ..\c_extensions\stacked_disks.h.
    	Refer to that file and the structure it contains
    	for details of the model.
    	List of default parameters:
         scale           = 0.01 
         radius          = 3000.0 [A]
         core_thick      = 10.0 [A]
         layer_thick     = 15.0 [A]
         core_sld        = 4e-006 [1/A�]
         layer_sld       = -4e-007 [1/A�]
         solvent_sld     = 5e-006 [1/A�]
         n_stacking      = 1.0 
         sigma_d         = 0.0 
         background      = 0.001 [1/cm]
         axis_theta      = 0.0 [rad]
         axis_phi        = 0.0 [rad]

    """
        
    def __init__(self):
        """ Initialization """
        
        # Initialize BaseComponent first, then sphere
        BaseComponent.__init__(self)
        CStackedDisksModel.__init__(self)
        
        ## Name of the model
        self.name = "StackedDisksModel"
        ## Model description
        self.description =""""""
       
		## Parameter details [units, min, max]
        self.details = {}
        self.details['scale'] = ['', None, None]
        self.details['radius'] = ['[A]', None, None]
        self.details['core_thick'] = ['[A]', None, None]
        self.details['layer_thick'] = ['[A]', None, None]
        self.details['core_sld'] = ['[1/A�]', None, None]
        self.details['layer_sld'] = ['[1/A�]', None, None]
        self.details['solvent_sld'] = ['[1/A�]', None, None]
        self.details['n_stacking'] = ['', None, None]
        self.details['sigma_d'] = ['', None, None]
        self.details['background'] = ['[1/cm]', None, None]
        self.details['axis_theta'] = ['[rad]', None, None]
        self.details['axis_phi'] = ['[rad]', None, None]

		## fittable parameters
        self.fixed=['core_thick.width', 'layer_thick.width', 'radius.width', 'axis_theta.width', 'axis_phi.width']
        
        ## parameters with orientation
        self.orientation_params =['axis_phi', 'axis_theta', 'axis_phi.width', 'axis_theta.width']
   
    def clone(self):
        """ Return a identical copy of self """
        return self._clone(StackedDisksModel())   
   
    def run(self, x = 0.0):
        """ Evaluate the model
            @param x: input q, or [q,phi]
            @return: scattering function P(q)
        """
        
        return CStackedDisksModel.run(self, x)
   
    def runXY(self, x = 0.0):
        """ Evaluate the model in cartesian coordinates
            @param x: input q, or [qx, qy]
            @return: scattering function P(q)
        """
        
        return CStackedDisksModel.runXY(self, x)
        
    def evalDistribition(self, x = []):
        """ Evaluate the model in cartesian coordinates
            @param x: input q[], or [qx[], qy[]]
            @return: scattering function P(q[])
        """
        return CStackedDisksModel.evalDistribition(self, x)
        
    def calculate_ER(self):
        """ Calculate the effective radius for P(q)*S(q)
            @param x: input q, or [q,phi]
            @return: the value of the effective radius
        """       
        return CStackedDisksModel.calculate_ER(self)
        
    def set_dispersion(self, parameter, dispersion):
        """
            Set the dispersion object for a model parameter
            @param parameter: name of the parameter [string]
            @dispersion: dispersion object of type DispersionModel
        """
        return CStackedDisksModel.set_dispersion(self, parameter, dispersion.cdisp)
        
   
# End of file
