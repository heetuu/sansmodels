#!/usr/bin/env python

##############################################################################
#	This software was developed by the University of Tennessee as part of the
#	Distributed Data Analysis of Neutron Scattering Experiments (DANSE)
#	project funded by the US National Science Foundation.
#
#	If you use DANSE applications to do scientific research that leads to
#	publication, we ask that you acknowledge the use of the software with the
#	following sentence:
#
#	"This work benefited from DANSE software developed under NSF award DMR-0520547."
#
#	copyright 2008, University of Tennessee
##############################################################################


""" 
Provide functionality for a C extension model

:WARNING: THIS FILE WAS GENERATED BY WRAPPERGENERATOR.PY
         DO NOT MODIFY THIS FILE, MODIFY ..\c_extensions\capcyl.h
         AND RE-RUN THE GENERATOR SCRIPT

"""

from sans.models.BaseComponent import BaseComponent
from sans_extension.c_models import CCappedCylinderModel
import copy    
    
class CappedCylinderModel(CCappedCylinderModel, BaseComponent):
    """ 
    Class that evaluates a CappedCylinderModel model. 
    This file was auto-generated from ..\c_extensions\capcyl.h.
    Refer to that file and the structure it contains
    for details of the model.
    List of default parameters:
         scale           = 1.0 
         rad_cyl         = 20.0 [A]
         len_cyl         = 400.0 [A]
         rad_cap         = 40.0 [A]
         sld_capcyl      = 1e-006 [1/A^(2)]
         sld_solv        = 6.3e-006 [1/A^(2)]
         background      = 0.0 [1/cm]
         theta           = 0.0 [rad]
         phi             = 0.0 [rad]

    """
        
    def __init__(self):
        """ Initialization """
        
        # Initialize BaseComponent first, then sphere
        BaseComponent.__init__(self)
        CCappedCylinderModel.__init__(self)
        
        ## Name of the model
        self.name = "CappedCylinderModel"
        ## Model description
        self.description ="""Calculates the scattering from a cylinder with spherical section end-caps.
		That is, a sphereocylinder
		with end caps that have a radius larger than
		that of the cylinder and the center of the
		end cap radius lies within the cylinder.
		Note: As the length of cylinder -->0,
		it becomes a ConvexLens.
		It must be that rad_cyl <(=) rad_cap.
		[Parameters];
		scale: volume fraction of spheres,
		background:incoherent background,
		rad_cyl: radius of the cylinder,
		len_cyl: length of the cylinder,
		rad_cap: radius of the semi-spherical cap,
		sld_capcyl: SLD of the capped cylinder,
		sld_solv: SLD of the solvent."""
       
        ## Parameter details [units, min, max]
        self.details = {}
        self.details['scale'] = ['', None, None]
        self.details['rad_cyl'] = ['[A]', None, None]
        self.details['len_cyl'] = ['[A]', None, None]
        self.details['rad_cap'] = ['[A]', None, None]
        self.details['sld_capcyl'] = ['[1/A^(2)]', None, None]
        self.details['sld_solv'] = ['[1/A^(2)]', None, None]
        self.details['background'] = ['[1/cm]', None, None]
        self.details['theta'] = ['[rad]', None, None]
        self.details['phi'] = ['[rad]', None, None]

        ## fittable parameters
        self.fixed=['rad_cyl.width', 'len_cyl', 'rad_cap', 'phi.width', 'theta.width']
        
        ## non-fittable parameters
        self.non_fittable=[]
        
        ## parameters with orientation
        self.orientation_params =['phi', 'theta', 'phi.width', 'theta.width']
   
    def clone(self):
        """ Return a identical copy of self """
        return self._clone(CappedCylinderModel())   
        
    def __getstate__(self):
        """
        return object state for pickling and copying
        """
        model_state = {'params': self.params, 'dispersion': self.dispersion, 'log': self.log}
        
        return self.__dict__, model_state
        
    def __setstate__(self, state):
        """
        create object from pickled state
        
        :param state: the state of the current model
        
        """
        
        self.__dict__, model_state = state
        self.params = model_state['params']
        self.dispersion = model_state['dispersion']
        self.log = model_state['log']
       	
   
    def run(self, x=0.0):
        """ 
        Evaluate the model
        
        :param x: input q, or [q,phi]
        
        :return: scattering function P(q)
        
        """
        
        return CCappedCylinderModel.run(self, x)
   
    def runXY(self, x=0.0):
        """ 
        Evaluate the model in cartesian coordinates
        
        :param x: input q, or [qx, qy]
        
        :return: scattering function P(q)
        
        """
        
        return CCappedCylinderModel.runXY(self, x)
        
    def evalDistribution(self, x=[]):
        """ 
        Evaluate the model in cartesian coordinates
        
        :param x: input q[], or [qx[], qy[]]
        
        :return: scattering function P(q[])
        
        """
        return CCappedCylinderModel.evalDistribution(self, x)
        
    def calculate_ER(self):
        """ 
        Calculate the effective radius for P(q)*S(q)
        
        :return: the value of the effective radius
        
        """       
        return CCappedCylinderModel.calculate_ER(self)
        
    def set_dispersion(self, parameter, dispersion):
        """
        Set the dispersion object for a model parameter
        
        :param parameter: name of the parameter [string]
        :param dispersion: dispersion object of type DispersionModel
        
        """
        return CCappedCylinderModel.set_dispersion(self, parameter, dispersion.cdisp)
        
   
# End of file
