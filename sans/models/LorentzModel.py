#!/usr/bin/env python
""" 
    Provide F(x) = scale/( 1 + (x*L)^2 ) + bkd
    Lorentz (Ornstein-Zernicke) function as a BaseComponent model
"""

from sans.models.BaseComponent import BaseComponent
import math

class LorentzModel(BaseComponent):
   
    """
        Class that evaluates a Lorentz (Ornstein-Zernicke) model.
        
        F(x) = scale/( 1 + (x*L)^2 ) + bkd
        
        The model has three parameters: 
            L     =  screen Length
            scale  =  scale factor
            bkd    =  incoherent background
    """
        
    def __init__(self):
        """ Initialization """
        
        # Initialize BaseComponent first, then sphere
        BaseComponent.__init__(self)
        
        ## Name of the model
        self.name = "Lorentz"

        ## Define parameters
        self.params = {}
        self.params['length']      = 50.0
        self.params['scale']       = 1.0
        self.params['background']  = 0.0

        ## Parameter details [units, min, max]
        self.details = {}
        self.details['length']     = ['A', None, None]
        self.details['scale']      = ['', None, None]
        self.details['background'] = ['cm-1', None, None]
               
    def _lorentz(self, x):
        """
            Evaluate F(x) = scale/( 1 + (x*L)^2 ) + bkd
           
        """
        return self.params['scale']/( 1 + math.pow((x * self.params['length']),2))\
                + self.params['background']
       
   
    def run(self, x = 0.0):
        """ Evaluate the model
            @param x: input q-value (float or [float, float] as [r, theta])
            @return: (Lorentz value)
        """
        if x.__class__.__name__ == 'list':
            return self._lorentz(x[0]*math.cos(x[1]))*self._lorentz(x[0]*math.sin(x[1]))
        elif x.__class__.__name__ == 'tuple':
            raise ValueError, "Tuples are not allowed as input to BaseComponent models"
        else:
            return self._lorentz(x)
   
    def runXY(self, x = 0.0):
        """ Evaluate the model
            @param x: input q-value (float or [float, float] as [qx, qy])
            @return: Lorentz value
        """
        if x.__class__.__name__ == 'list':
            return self._lorentz(x[0])*self._lorentz(x[1])
        elif x.__class__.__name__ == 'tuple':
            raise ValueError, "Tuples are not allowed as input to BaseComponent models"
        else:
            return self._lorentz(x)
