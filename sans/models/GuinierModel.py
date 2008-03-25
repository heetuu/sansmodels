#!/usr/bin/env python
""" 
    Provide I(q) = I_0 exp ( - R_g^2 q^2 / 3.0)
    Guinier function as a BaseComponent model
"""

from sans.models.BaseComponent import BaseComponent
import math

class GuinierModel(BaseComponent):
    """ 
        Class that evaluates a Guinier model.
    
        I(q) = I_0 exp ( - R_g^2 q^2 / 3.0 )
     
        List of default parameters:
         I_0 = Scale
         R_g = Radius of gyration
          
    """
        
    def __init__(self):
        """ Initialization """
        
        # Initialize BaseComponent first, then sphere
        BaseComponent.__init__(self)
        
        ## Name of the model
        self.name = "Guinier"

        ## Define parameters
        self.params = {}
        self.params['scale']  = 1.0
        self.params['rg']     = 0.1

        ## Parameter details [units, min, max]
        self.details = {}
        self.details['scale'] = ['cm-1', None, None]
        self.details['rg']    = ['A', None, None]
               
    def _guinier(self, x):
        return self.params['scale'] * math.exp( -(self.params['rg']*x)**2 / 3.0 )  
   
    def run(self, x = 0.0):
        """ Evaluate the model
            @param x: input q-value (float or [float, float] as [r, theta])
            @return: (guinier value)
        """
        if x.__class__.__name__ == 'list':
            return self._guinier(x[0]*math.cos(x[1]))*self._guinier(x[0]*math.sin(x[1]))
        elif x.__class__.__name__ == 'tuple':
            raise ValueError, "Tuples are not allowed as input to BaseComponent models"
        else:
            return self._guinier(x)
   
    def runXY(self, x = 0.0):
        """ Evaluate the model
            @param x: input q-value (float or [float, float] as [qx, qy])
            @return: guinier value
        """
        if x.__class__.__name__ == 'list':
            return self._guinier(x[0])*self._guinier(x[1])
        elif x.__class__.__name__ == 'tuple':
            raise ValueError, "Tuples are not allowed as input to BaseComponent models"
        else:
            return self._guinier(x)
