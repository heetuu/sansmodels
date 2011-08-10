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
         DO NOT MODIFY THIS FILE, MODIFY ..\c_extensions\multishell.h
         AND RE-RUN THE GENERATOR SCRIPT

"""

from sans.models.BaseComponent import BaseComponent
from sans.models.sans_extension.c_models import CMultiShellModel
import copy    

def create_MultiShellModel():
    obj = MultiShellModel()
    #CMultiShellModel.__init__(obj) is called by MultiShellModel constructor
    return obj

class MultiShellModel(CMultiShellModel, BaseComponent):
    """ 
    Class that evaluates a MultiShellModel model. 
    This file was auto-generated from ..\c_extensions\multishell.h.
    Refer to that file and the structure it contains
    for details of the model.
    List of default parameters:
         scale           = 1.0 
         core_radius     = 60.0 [A]
         s_thickness     = 10.0 [A]
         w_thickness     = 10.0 [A]
         core_sld        = 6.4e-06 [1/A^(2)]
         shell_sld       = 4e-07 [1/A^(2)]
         n_pairs         = 2.0 
         background      = 0.0 [1/cm]

    """
        
    def __init__(self):
        """ Initialization """
        
        # Initialize BaseComponent first, then sphere
        BaseComponent.__init__(self)
        #apply(CMultiShellModel.__init__, (self,)) 
        CMultiShellModel.__init__(self)
        
        ## Name of the model
        self.name = "MultiShellModel"
        ## Model description
        self.description =""" MultiShell (Sphere) Model (or Multilamellar Vesicles): Model parameters;
		scale : scale factor
		core_radius : Core radius of the multishell
		s_thickness: shell thickness
		w_thickness: water thickness
		core_sld: core scattering length density
		shell_sld: shell scattering length density
		n_pairs:number of pairs of water/shell
		background: incoherent background"""
       
        ## Parameter details [units, min, max]
        self.details = {}
        self.details['scale'] = ['', None, None]
        self.details['core_radius'] = ['[A]', None, None]
        self.details['s_thickness'] = ['[A]', None, None]
        self.details['w_thickness'] = ['[A]', None, None]
        self.details['core_sld'] = ['[1/A^(2)]', None, None]
        self.details['shell_sld'] = ['[1/A^(2)]', None, None]
        self.details['n_pairs'] = ['', None, None]
        self.details['background'] = ['[1/cm]', None, None]

        ## fittable parameters
        self.fixed=['core_radius.width', 's_thickness.width', 'w_thickness.width']
        
        ## non-fittable parameters
        self.non_fittable = []
        
        ## parameters with orientation
        self.orientation_params = []

    def __setstate__(self, state):
        """
        restore the state of a model from pickle
        """
        self.__dict__, self.params, self.dispersion = state
        
    def __reduce_ex__(self, proto):
        """
        Overwrite the __reduce_ex__ of PyTypeObject *type call in the init of 
        c model.
        """
        state = (self.__dict__, self.params, self.dispersion)
        return (create_MultiShellModel,tuple(), state, None, None)
        
    def clone(self):
        """ Return a identical copy of self """
        return self._clone(MultiShellModel())   
       	
   
    def run(self, x=0.0):
        """ 
        Evaluate the model
        
        :param x: input q, or [q,phi]
        
        :return: scattering function P(q)
        
        """
        
        return CMultiShellModel.run(self, x)
   
    def runXY(self, x=0.0):
        """ 
        Evaluate the model in cartesian coordinates
        
        :param x: input q, or [qx, qy]
        
        :return: scattering function P(q)
        
        """
        
        return CMultiShellModel.runXY(self, x)
        
    def evalDistribution(self, x=[]):
        """ 
        Evaluate the model in cartesian coordinates
        
        :param x: input q[], or [qx[], qy[]]
        
        :return: scattering function P(q[])
        
        """
        return CMultiShellModel.evalDistribution(self, x)
        
    def calculate_ER(self):
        """ 
        Calculate the effective radius for P(q)*S(q)
        
        :return: the value of the effective radius
        
        """       
        return CMultiShellModel.calculate_ER(self)
        
    def set_dispersion(self, parameter, dispersion):
        """
        Set the dispersion object for a model parameter
        
        :param parameter: name of the parameter [string]
        :param dispersion: dispersion object of type DispersionModel
        
        """
        return CMultiShellModel.set_dispersion(self, parameter, dispersion.cdisp)
        
   
# End of file
