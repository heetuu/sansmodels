/** CCoreShellEllipsoidModel
 *
 * C extension 
 *
 * WARNING: THIS FILE WAS GENERATED BY WRAPPERGENERATOR.PY
 *          DO NOT MODIFY THIS FILE, MODIFY spheroid.h
 *          AND RE-RUN THE GENERATOR SCRIPT
 *
 * @author   M.Doucet / UTK
 */
 
#include <Python.h>
#include "structmember.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "spheroid.h"

/// Error object for raised exceptions
static PyObject * CCoreShellEllipsoidModelError = NULL;


// Class definition
typedef struct {
    PyObject_HEAD
    /// Parameters
    PyObject * params;
    /// Log for unit testing
    PyObject * log;
    /// Model parameters
	SpheroidParameters model_pars;
} CCoreShellEllipsoidModel;


static void
CCoreShellEllipsoidModel_dealloc(CCoreShellEllipsoidModel* self)
{
    self->ob_type->tp_free((PyObject*)self);
    

}

static PyObject *
CCoreShellEllipsoidModel_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    CCoreShellEllipsoidModel *self;
    
    self = (CCoreShellEllipsoidModel *)type->tp_alloc(type, 0);
   
    return (PyObject *)self;
}

static int
CCoreShellEllipsoidModel_init(CCoreShellEllipsoidModel *self, PyObject *args, PyObject *kwds)
{
    if (self != NULL) {
    	
    	// Create parameters
        self->params = PyDict_New();
        
        // Initialize parameter dictionary
        PyDict_SetItemString(self->params,"scale",Py_BuildValue("d",1.000000));
        PyDict_SetItemString(self->params,"axis_theta",Py_BuildValue("d",0.000000));
        PyDict_SetItemString(self->params,"polar_shell",Py_BuildValue("d",30.000000));
        PyDict_SetItemString(self->params,"sld_solvent",Py_BuildValue("d",0.000006));
        PyDict_SetItemString(self->params,"equat_shell",Py_BuildValue("d",250.000000));
        PyDict_SetItemString(self->params,"axis_phi",Py_BuildValue("d",0.000000));
        PyDict_SetItemString(self->params,"background",Py_BuildValue("d",0.001000));
        PyDict_SetItemString(self->params,"equat_core",Py_BuildValue("d",200.000000));
        PyDict_SetItemString(self->params,"polar_core",Py_BuildValue("d",20.000000));
        PyDict_SetItemString(self->params,"contrast",Py_BuildValue("d",0.000001));

         
        // Create empty log
        self->log = PyDict_New();
        
        

    }
    return 0;
}

static PyMemberDef CCoreShellEllipsoidModel_members[] = {
    {"params", T_OBJECT, offsetof(CCoreShellEllipsoidModel, params), 0,
     "Parameters"},
    {"log", T_OBJECT, offsetof(CCoreShellEllipsoidModel, log), 0,
     "Log"},
    {NULL}  /* Sentinel */
};

/** Read double from PyObject
    @param p PyObject
    @return double
*/
double CCoreShellEllipsoidModel_readDouble(PyObject *p) {
    if (PyFloat_Check(p)==1) {
        return (double)(((PyFloatObject *)(p))->ob_fval);
    } else if (PyInt_Check(p)==1) {
        return (double)(((PyIntObject *)(p))->ob_ival);
    } else if (PyLong_Check(p)==1) {
        return (double)PyLong_AsLong(p);
    } else {
        return 0.0;
    }
}


/**
 * Function to call to evaluate model
 * @param args: input q or [q,phi]
 * @return: function value
 */
static PyObject * run(CCoreShellEllipsoidModel *self, PyObject *args) {
	double q_value, phi_value;
	PyObject* pars;
	int npars;
	
	// Get parameters
	
	// Reader parameter dictionary
    self->model_pars.scale = PyFloat_AsDouble( PyDict_GetItemString(self->params, "scale") );
    self->model_pars.axis_theta = PyFloat_AsDouble( PyDict_GetItemString(self->params, "axis_theta") );
    self->model_pars.polar_shell = PyFloat_AsDouble( PyDict_GetItemString(self->params, "polar_shell") );
    self->model_pars.sld_solvent = PyFloat_AsDouble( PyDict_GetItemString(self->params, "sld_solvent") );
    self->model_pars.equat_shell = PyFloat_AsDouble( PyDict_GetItemString(self->params, "equat_shell") );
    self->model_pars.axis_phi = PyFloat_AsDouble( PyDict_GetItemString(self->params, "axis_phi") );
    self->model_pars.background = PyFloat_AsDouble( PyDict_GetItemString(self->params, "background") );
    self->model_pars.equat_core = PyFloat_AsDouble( PyDict_GetItemString(self->params, "equat_core") );
    self->model_pars.polar_core = PyFloat_AsDouble( PyDict_GetItemString(self->params, "polar_core") );
    self->model_pars.contrast = PyFloat_AsDouble( PyDict_GetItemString(self->params, "contrast") );

	
	// Get input and determine whether we have to supply a 1D or 2D return value.
	if ( !PyArg_ParseTuple(args,"O",&pars) ) {
	    PyErr_SetString(CCoreShellEllipsoidModelError, 
	    	"CCoreShellEllipsoidModel.run expects a q value.");
		return NULL;
	}
	  
	// Check params
	if( PyList_Check(pars)==1) {
		
		// Length of list should be 2 for I(q,phi)
	    npars = PyList_GET_SIZE(pars); 
	    if(npars!=2) {
	    	PyErr_SetString(CCoreShellEllipsoidModelError, 
	    		"CCoreShellEllipsoidModel.run expects a double or a list of dimension 2.");
	    	return NULL;
	    }
	    // We have a vector q, get the q and phi values at which
	    // to evaluate I(q,phi)
	    q_value = CCoreShellEllipsoidModel_readDouble(PyList_GET_ITEM(pars,0));
	    phi_value = CCoreShellEllipsoidModel_readDouble(PyList_GET_ITEM(pars,1));
	    // Skip zero
	    if (q_value==0) {
	    	return Py_BuildValue("d",0.0);
	    }
		return Py_BuildValue("d",spheroid_analytical_2D(&(self->model_pars),q_value,phi_value));

	} else {

		// We have a scalar q, we will evaluate I(q)
		q_value = CCoreShellEllipsoidModel_readDouble(pars);		
		
		return Py_BuildValue("d",spheroid_analytical_1D(&(self->model_pars),q_value));
	}	
}

/**
 * Function to call to evaluate model in cartesian coordinates
 * @param args: input q or [qx, qy]]
 * @return: function value
 */
static PyObject * runXY(CCoreShellEllipsoidModel *self, PyObject *args) {
	double qx_value, qy_value;
	PyObject* pars;
	int npars;
	
	// Get parameters
	
	// Reader parameter dictionary
    self->model_pars.scale = PyFloat_AsDouble( PyDict_GetItemString(self->params, "scale") );
    self->model_pars.axis_theta = PyFloat_AsDouble( PyDict_GetItemString(self->params, "axis_theta") );
    self->model_pars.polar_shell = PyFloat_AsDouble( PyDict_GetItemString(self->params, "polar_shell") );
    self->model_pars.sld_solvent = PyFloat_AsDouble( PyDict_GetItemString(self->params, "sld_solvent") );
    self->model_pars.equat_shell = PyFloat_AsDouble( PyDict_GetItemString(self->params, "equat_shell") );
    self->model_pars.axis_phi = PyFloat_AsDouble( PyDict_GetItemString(self->params, "axis_phi") );
    self->model_pars.background = PyFloat_AsDouble( PyDict_GetItemString(self->params, "background") );
    self->model_pars.equat_core = PyFloat_AsDouble( PyDict_GetItemString(self->params, "equat_core") );
    self->model_pars.polar_core = PyFloat_AsDouble( PyDict_GetItemString(self->params, "polar_core") );
    self->model_pars.contrast = PyFloat_AsDouble( PyDict_GetItemString(self->params, "contrast") );

	
	// Get input and determine whether we have to supply a 1D or 2D return value.
	if ( !PyArg_ParseTuple(args,"O",&pars) ) {
	    PyErr_SetString(CCoreShellEllipsoidModelError, 
	    	"CCoreShellEllipsoidModel.run expects a q value.");
		return NULL;
	}
	  
	// Check params
	if( PyList_Check(pars)==1) {
		
		// Length of list should be 2 for I(qx, qy))
	    npars = PyList_GET_SIZE(pars); 
	    if(npars!=2) {
	    	PyErr_SetString(CCoreShellEllipsoidModelError, 
	    		"CCoreShellEllipsoidModel.run expects a double or a list of dimension 2.");
	    	return NULL;
	    }
	    // We have a vector q, get the qx and qy values at which
	    // to evaluate I(qx,qy)
	    qx_value = CCoreShellEllipsoidModel_readDouble(PyList_GET_ITEM(pars,0));
	    qy_value = CCoreShellEllipsoidModel_readDouble(PyList_GET_ITEM(pars,1));
		return Py_BuildValue("d",spheroid_analytical_2DXY(&(self->model_pars),qx_value,qy_value));

	} else {

		// We have a scalar q, we will evaluate I(q)
		qx_value = CCoreShellEllipsoidModel_readDouble(pars);		
		
		return Py_BuildValue("d",spheroid_analytical_1D(&(self->model_pars),qx_value));
	}	
}

static PyObject * reset(CCoreShellEllipsoidModel *self, PyObject *args) {
    

    return Py_BuildValue("d",0.0);
}


static PyMethodDef CCoreShellEllipsoidModel_methods[] = {
    {"run",      (PyCFunction)run     , METH_VARARGS,
      "Evaluate the model at a given Q or Q, phi"},
    {"runXY",      (PyCFunction)runXY     , METH_VARARGS,
      "Evaluate the model at a given Q or Qx, Qy"},
    {"reset",    (PyCFunction)reset   , METH_VARARGS,
      "Reset pair correlation"},
    //{"numerical_1D",      (PyCFunction)numerical_1D     , METH_VARARGS,
    //  "Evaluate the 1D model at a given Q"},
   {NULL}
};

static PyTypeObject CCoreShellEllipsoidModelType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "CCoreShellEllipsoidModel",             /*tp_name*/
    sizeof(CCoreShellEllipsoidModel),             /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)CCoreShellEllipsoidModel_dealloc, /*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
    "CCoreShellEllipsoidModel objects",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,		               /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    CCoreShellEllipsoidModel_methods,             /* tp_methods */
    CCoreShellEllipsoidModel_members,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)CCoreShellEllipsoidModel_init,      /* tp_init */
    0,                         /* tp_alloc */
    CCoreShellEllipsoidModel_new,                 /* tp_new */
};


static PyMethodDef module_methods[] = {
    {NULL} 
};

/**
 * Function used to add the model class to a module
 * @param module: module to add the class to
 */ 
void addCCoreShellEllipsoidModel(PyObject *module) {
	PyObject *d;
	
    if (PyType_Ready(&CCoreShellEllipsoidModelType) < 0)
        return;

    Py_INCREF(&CCoreShellEllipsoidModelType);
    PyModule_AddObject(module, "CCoreShellEllipsoidModel", (PyObject *)&CCoreShellEllipsoidModelType);
    
    d = PyModule_GetDict(module);
    CCoreShellEllipsoidModelError = PyErr_NewException("CCoreShellEllipsoidModel.error", NULL, NULL);
    PyDict_SetItemString(d, "CCoreShellEllipsoidModelError", CCoreShellEllipsoidModelError);
}

