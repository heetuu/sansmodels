/**
	This software was developed by the University of Tennessee as part of the
	Distributed Data Analysis of Neutron Scattering Experiments (DANSE)
	project funded by the US National Science Foundation.

	If you use DANSE applications to do scientific research that leads to
	publication, we ask that you acknowledge the use of the software with the
	following sentence:

	"This work benefited from DANSE software developed under NSF award DMR-0520547."

	copyright 2008, University of Tennessee
 */

/** CVesicleModel
 *
 * C extension 
 *
 * WARNING: THIS FILE WAS GENERATED BY WRAPPERGENERATOR.PY
 *          DO NOT MODIFY THIS FILE, MODIFY vesicle.h
 *          AND RE-RUN THE GENERATOR SCRIPT
 *
 */
#define NO_IMPORT_ARRAY
#define PY_ARRAY_UNIQUE_SYMBOL PyArray_API_sans
 
extern "C" {
#include <Python.h>
#include <arrayobject.h>
#include "structmember.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "vesicle.h"
}

#include "models.hh"
#include "dispersion_visitor.hh"

/// Error object for raised exceptions
static PyObject * CVesicleModelError = NULL;


// Class definition
typedef struct {
    PyObject_HEAD
    /// Parameters
    PyObject * params;
    /// Dispersion parameters
    PyObject * dispersion;
    /// Underlying model object
    VesicleModel * model;
    /// Log for unit testing
    PyObject * log;
} CVesicleModel;


static void
CVesicleModel_dealloc(CVesicleModel* self)
{
    Py_DECREF(self->params);
    Py_DECREF(self->dispersion);
    Py_DECREF(self->log);
    delete self->model;
    self->ob_type->tp_free((PyObject*)self);
    

}

static PyObject *
CVesicleModel_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    CVesicleModel *self;
    
    self = (CVesicleModel *)type->tp_alloc(type, 0);
   
    return (PyObject *)self;
}

static int
CVesicleModel_init(CVesicleModel *self, PyObject *args, PyObject *kwds)
{
    if (self != NULL) {
    	
    	// Create parameters
        self->params = PyDict_New();
        self->dispersion = PyDict_New();
        self->model = new VesicleModel();
        
        // Initialize parameter dictionary
        PyDict_SetItemString(self->params,"core_sld",Py_BuildValue("d",0.000006));
        PyDict_SetItemString(self->params,"thickness",Py_BuildValue("d",30.000000));
        PyDict_SetItemString(self->params,"scale",Py_BuildValue("d",1.000000));
        PyDict_SetItemString(self->params,"radius",Py_BuildValue("d",100.000000));
        PyDict_SetItemString(self->params,"background",Py_BuildValue("d",0.000000));
        PyDict_SetItemString(self->params,"shell_sld",Py_BuildValue("d",0.000000));
        // Initialize dispersion / averaging parameter dict
        DispersionVisitor* visitor = new DispersionVisitor();
        PyObject * disp_dict;
        disp_dict = PyDict_New();
        self->model->radius.dispersion->accept_as_source(visitor, self->model->radius.dispersion, disp_dict);
        PyDict_SetItemString(self->dispersion, "radius", disp_dict);
        disp_dict = PyDict_New();
        self->model->thickness.dispersion->accept_as_source(visitor, self->model->thickness.dispersion, disp_dict);
        PyDict_SetItemString(self->dispersion, "thickness", disp_dict);


         
        // Create empty log
        self->log = PyDict_New();
        
        

    }
    return 0;
}

static PyMemberDef CVesicleModel_members[] = {
    {"params", T_OBJECT, offsetof(CVesicleModel, params), 0,
     "Parameters"},
	{"dispersion", T_OBJECT, offsetof(CVesicleModel, dispersion), 0,
	  "Dispersion parameters"},     
    {"log", T_OBJECT, offsetof(CVesicleModel, log), 0,
     "Log"},
    {NULL}  /* Sentinel */
};

/** Read double from PyObject
    @param p PyObject
    @return double
*/
double CVesicleModel_readDouble(PyObject *p) {
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
 * @param args: input numpy array q[] 
 * @return: numpy array object 
 */
 
static PyObject *evaluateOneDim(VesicleModel* model, PyArrayObject *q){
    PyArrayObject *result;
   
    // Check validity of array q , q must be of dimension 1, an array of double
    if (q->nd != 1 || q->descr->type_num != PyArray_DOUBLE)
    {
        //const char * message= "Invalid array: q->nd=%d,type_num=%d\n",q->nd,q->descr->type_num;
        //PyErr_SetString(PyExc_ValueError , message);
        return NULL;
    }
    result = (PyArrayObject *)PyArray_FromDims(q->nd, (int *)(q->dimensions), 
										  PyArray_DOUBLE);
	if (result == NULL) {
        const char * message= "Could not create result ";
        PyErr_SetString(PyExc_RuntimeError , message);
		return NULL;
	}
	 for (int i = 0; i < q->dimensions[0]; i++){
      double q_value  = *(double *)(q->data + i*q->strides[0]);
      double *result_value = (double *)(result->data + i*result->strides[0]);
      *result_value =(*model)(q_value);
	}
    return PyArray_Return(result); 
 }

 /**
 * Function to call to evaluate model
 * @param args: input numpy array  [x[],y[]]
 * @return: numpy array object 
 */
 static PyObject * evaluateTwoDimXY( VesicleModel* model, 
                              PyArrayObject *x, PyArrayObject *y)
 {
    PyArrayObject *result;
    int i,j, x_len, y_len, dims[1];
    //check validity of input vectors
    if (x->nd != 1 || x->descr->type_num != PyArray_DOUBLE
        || y->nd != 1 || y->descr->type_num != PyArray_DOUBLE
        || y->dimensions[0] != x->dimensions[0]){
        const char * message= "evaluateTwoDimXY  expect 2 numpy arrays";
        PyErr_SetString(PyExc_ValueError , message); 
        return NULL;
    }
   
	if (PyArray_Check(x) && PyArray_Check(y)) {
		
	    x_len = dims[0]= x->dimensions[0];
        y_len = dims[0]= y->dimensions[0];
	    
	    // Make a new double matrix of same dims
        result=(PyArrayObject *) PyArray_FromDims(1,dims,NPY_DOUBLE);
        if (result == NULL){
	    const char * message= "Could not create result ";
        PyErr_SetString(PyExc_RuntimeError , message);
	    return NULL;
	    }
       
        /* Do the calculation. */
        for ( i=0; i< x_len; i++) {
            double x_value = *(double *)(x->data + i*x->strides[0]);
  		    double y_value = *(double *)(y->data + i*y->strides[0]);
  			double *result_value = (double *)(result->data +
  			      i*result->strides[0]);
  			*result_value = (*model)(x_value, y_value);
        }           
        return PyArray_Return(result); 
        
        }else{
		    PyErr_SetString(CVesicleModelError, 
                   "CVesicleModel.evaluateTwoDimXY couldn't run.");
	        return NULL;
		}      	
}
/**
 *  evalDistribution function evaluate a model function with input vector
 *  @param args: input q as vector or [qx, qy] where qx, qy are vectors
 *
 */ 
static PyObject * evalDistribution(CVesicleModel *self, PyObject *args){
	PyObject *qx, *qy;
	PyArrayObject * pars;
	int npars ,mpars;
	
	// Get parameters
	
	    // Reader parameter dictionary
    self->model->core_sld = PyFloat_AsDouble( PyDict_GetItemString(self->params, "core_sld") );
    self->model->thickness = PyFloat_AsDouble( PyDict_GetItemString(self->params, "thickness") );
    self->model->scale = PyFloat_AsDouble( PyDict_GetItemString(self->params, "scale") );
    self->model->radius = PyFloat_AsDouble( PyDict_GetItemString(self->params, "radius") );
    self->model->background = PyFloat_AsDouble( PyDict_GetItemString(self->params, "background") );
    self->model->shell_sld = PyFloat_AsDouble( PyDict_GetItemString(self->params, "shell_sld") );
    // Read in dispersion parameters
    PyObject* disp_dict;
    DispersionVisitor* visitor = new DispersionVisitor();
    disp_dict = PyDict_GetItemString(self->dispersion, "radius");
    self->model->radius.dispersion->accept_as_destination(visitor, self->model->radius.dispersion, disp_dict);
    disp_dict = PyDict_GetItemString(self->dispersion, "thickness");
    self->model->thickness.dispersion->accept_as_destination(visitor, self->model->thickness.dispersion, disp_dict);

	
	// Get input and determine whether we have to supply a 1D or 2D return value.
	if ( !PyArg_ParseTuple(args,"O",&pars) ) {
	    PyErr_SetString(CVesicleModelError, 
	    	"CVesicleModel.evalDistribution expects a q value.");
		return NULL;
	}
    // Check params
	
    if(PyArray_Check(pars)==1) {
		
	    // Length of list should 1 or 2
	    npars = pars->nd; 
	    if(npars==1) {
	        // input is a numpy array
	        if (PyArray_Check(pars)) {
		        return evaluateOneDim(self->model, (PyArrayObject*)pars); 
		    }
		}else{
		    PyErr_SetString(CVesicleModelError, 
                   "CVesicleModel.evalDistribution expect numpy array of one dimension.");
	        return NULL;
		}
    }else if( PyList_Check(pars)==1) {
    	// Length of list should be 2 for I(qx,qy)
	    mpars = PyList_GET_SIZE(pars); 
	    if(mpars!=2) {
	    	PyErr_SetString(CVesicleModelError, 
	    		"CVesicleModel.evalDistribution expects a list of dimension 2.");
	    	return NULL;
	    }
	     qx = PyList_GET_ITEM(pars,0);
	     qy = PyList_GET_ITEM(pars,1);
	     if (PyArray_Check(qx) && PyArray_Check(qy)) {
	         return evaluateTwoDimXY(self->model, (PyArrayObject*)qx,
		           (PyArrayObject*)qy);
		 }else{
		    PyErr_SetString(CVesicleModelError, 
                   "CVesicleModel.evalDistribution expect 2 numpy arrays in list.");
	        return NULL;
	     }
	}
	PyErr_SetString(CVesicleModelError, 
                   "CVesicleModel.evalDistribution couln't be run.");
	return NULL;
	
}

/**
 * Function to call to evaluate model
 * @param args: input q or [q,phi]
 * @return: function value
 */
static PyObject * run(CVesicleModel *self, PyObject *args) {
	double q_value, phi_value;
	PyObject* pars;
	int npars;
	
	// Get parameters
	
	    // Reader parameter dictionary
    self->model->core_sld = PyFloat_AsDouble( PyDict_GetItemString(self->params, "core_sld") );
    self->model->thickness = PyFloat_AsDouble( PyDict_GetItemString(self->params, "thickness") );
    self->model->scale = PyFloat_AsDouble( PyDict_GetItemString(self->params, "scale") );
    self->model->radius = PyFloat_AsDouble( PyDict_GetItemString(self->params, "radius") );
    self->model->background = PyFloat_AsDouble( PyDict_GetItemString(self->params, "background") );
    self->model->shell_sld = PyFloat_AsDouble( PyDict_GetItemString(self->params, "shell_sld") );
    // Read in dispersion parameters
    PyObject* disp_dict;
    DispersionVisitor* visitor = new DispersionVisitor();
    disp_dict = PyDict_GetItemString(self->dispersion, "radius");
    self->model->radius.dispersion->accept_as_destination(visitor, self->model->radius.dispersion, disp_dict);
    disp_dict = PyDict_GetItemString(self->dispersion, "thickness");
    self->model->thickness.dispersion->accept_as_destination(visitor, self->model->thickness.dispersion, disp_dict);

	
	// Get input and determine whether we have to supply a 1D or 2D return value.
	if ( !PyArg_ParseTuple(args,"O",&pars) ) {
	    PyErr_SetString(CVesicleModelError, 
	    	"CVesicleModel.run expects a q value.");
		return NULL;
	}
	  
	// Check params
	if( PyList_Check(pars)==1) {
		
		// Length of list should be 2 for I(q,phi)
	    npars = PyList_GET_SIZE(pars); 
	    if(npars!=2) {
	    	PyErr_SetString(CVesicleModelError, 
	    		"CVesicleModel.run expects a double or a list of dimension 2.");
	    	return NULL;
	    }
	    // We have a vector q, get the q and phi values at which
	    // to evaluate I(q,phi)
	    q_value = CVesicleModel_readDouble(PyList_GET_ITEM(pars,0));
	    phi_value = CVesicleModel_readDouble(PyList_GET_ITEM(pars,1));
	    // Skip zero
	    if (q_value==0) {
	    	return Py_BuildValue("d",0.0);
	    }
		return Py_BuildValue("d",(*(self->model)).evaluate_rphi(q_value,phi_value));

	} else {

		// We have a scalar q, we will evaluate I(q)
		q_value = CVesicleModel_readDouble(pars);		
		
		return Py_BuildValue("d",(*(self->model))(q_value));
	}	
}
/**
 * Function to call to calculate_ER
 * @return: effective radius value 
 */
static PyObject * calculate_ER(CVesicleModel *self) {

	PyObject* pars;
	int npars;
	
	// Get parameters
	
	    // Reader parameter dictionary
    self->model->core_sld = PyFloat_AsDouble( PyDict_GetItemString(self->params, "core_sld") );
    self->model->thickness = PyFloat_AsDouble( PyDict_GetItemString(self->params, "thickness") );
    self->model->scale = PyFloat_AsDouble( PyDict_GetItemString(self->params, "scale") );
    self->model->radius = PyFloat_AsDouble( PyDict_GetItemString(self->params, "radius") );
    self->model->background = PyFloat_AsDouble( PyDict_GetItemString(self->params, "background") );
    self->model->shell_sld = PyFloat_AsDouble( PyDict_GetItemString(self->params, "shell_sld") );
    // Read in dispersion parameters
    PyObject* disp_dict;
    DispersionVisitor* visitor = new DispersionVisitor();
    disp_dict = PyDict_GetItemString(self->dispersion, "radius");
    self->model->radius.dispersion->accept_as_destination(visitor, self->model->radius.dispersion, disp_dict);
    disp_dict = PyDict_GetItemString(self->dispersion, "thickness");
    self->model->thickness.dispersion->accept_as_destination(visitor, self->model->thickness.dispersion, disp_dict);

		
	return Py_BuildValue("d",(*(self->model)).calculate_ER());

}
/**
 * Function to call to evaluate model in cartesian coordinates
 * @param args: input q or [qx, qy]]
 * @return: function value
 */
static PyObject * runXY(CVesicleModel *self, PyObject *args) {
	double qx_value, qy_value;
	PyObject* pars;
	int npars;
	
	// Get parameters
	
	    // Reader parameter dictionary
    self->model->core_sld = PyFloat_AsDouble( PyDict_GetItemString(self->params, "core_sld") );
    self->model->thickness = PyFloat_AsDouble( PyDict_GetItemString(self->params, "thickness") );
    self->model->scale = PyFloat_AsDouble( PyDict_GetItemString(self->params, "scale") );
    self->model->radius = PyFloat_AsDouble( PyDict_GetItemString(self->params, "radius") );
    self->model->background = PyFloat_AsDouble( PyDict_GetItemString(self->params, "background") );
    self->model->shell_sld = PyFloat_AsDouble( PyDict_GetItemString(self->params, "shell_sld") );
    // Read in dispersion parameters
    PyObject* disp_dict;
    DispersionVisitor* visitor = new DispersionVisitor();
    disp_dict = PyDict_GetItemString(self->dispersion, "radius");
    self->model->radius.dispersion->accept_as_destination(visitor, self->model->radius.dispersion, disp_dict);
    disp_dict = PyDict_GetItemString(self->dispersion, "thickness");
    self->model->thickness.dispersion->accept_as_destination(visitor, self->model->thickness.dispersion, disp_dict);

	
	// Get input and determine whether we have to supply a 1D or 2D return value.
	if ( !PyArg_ParseTuple(args,"O",&pars) ) {
	    PyErr_SetString(CVesicleModelError, 
	    	"CVesicleModel.run expects a q value.");
		return NULL;
	}
	  
	// Check params
	if( PyList_Check(pars)==1) {
		
		// Length of list should be 2 for I(qx, qy))
	    npars = PyList_GET_SIZE(pars); 
	    if(npars!=2) {
	    	PyErr_SetString(CVesicleModelError, 
	    		"CVesicleModel.run expects a double or a list of dimension 2.");
	    	return NULL;
	    }
	    // We have a vector q, get the qx and qy values at which
	    // to evaluate I(qx,qy)
	    qx_value = CVesicleModel_readDouble(PyList_GET_ITEM(pars,0));
	    qy_value = CVesicleModel_readDouble(PyList_GET_ITEM(pars,1));
	    return Py_BuildValue("d",(*(self->model))(qx_value,qy_value));

	} else {

		// We have a scalar q, we will evaluate I(q)
		qx_value = CVesicleModel_readDouble(pars);		
		
		return Py_BuildValue("d",(*(self->model))(qx_value));
	}	
}

static PyObject * reset(CVesicleModel *self, PyObject *args) {
    

    return Py_BuildValue("d",0.0);
}

static PyObject * set_dispersion(CVesicleModel *self, PyObject *args) {
	PyObject * disp;
	const char * par_name;

	if ( !PyArg_ParseTuple(args,"sO", &par_name, &disp) ) {
	    PyErr_SetString(CVesicleModelError,
	    	"CVesicleModel.set_dispersion expects a DispersionModel object.");
		return NULL;
	}
	void *temp = PyCObject_AsVoidPtr(disp);
	DispersionModel * dispersion = static_cast<DispersionModel *>(temp);


	// Ugliness necessary to go from python to C
	    // TODO: refactor this
    if (!strcmp(par_name, "radius")) {
        self->model->radius.dispersion = dispersion;
    } else    if (!strcmp(par_name, "thickness")) {
        self->model->thickness.dispersion = dispersion;
    } else {
	    PyErr_SetString(CVesicleModelError,
	    	"CVesicleModel.set_dispersion expects a valid parameter name.");
		return NULL;
	}

	DispersionVisitor* visitor = new DispersionVisitor();
	PyObject * disp_dict = PyDict_New();
	dispersion->accept_as_source(visitor, dispersion, disp_dict);
	PyDict_SetItemString(self->dispersion, par_name, disp_dict);
    return Py_BuildValue("i",1);
}


static PyMethodDef CVesicleModel_methods[] = {
    {"run",      (PyCFunction)run     , METH_VARARGS,
      "Evaluate the model at a given Q or Q, phi"},
    {"runXY",      (PyCFunction)runXY     , METH_VARARGS,
      "Evaluate the model at a given Q or Qx, Qy"},
    {"calculate_ER",      (PyCFunction)calculate_ER     , METH_VARARGS,
      "Evaluate the model at a given Q or Q, phi"},
      
    {"evalDistribution",  (PyCFunction)evalDistribution , METH_VARARGS,
      "Evaluate the model at a given Q or Qx, Qy vector "},
    {"reset",    (PyCFunction)reset   , METH_VARARGS,
      "Reset pair correlation"},
    {"set_dispersion",      (PyCFunction)set_dispersion     , METH_VARARGS,
      "Set the dispersion model for a given parameter"},
   {NULL}
};

static PyTypeObject CVesicleModelType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "CVesicleModel",             /*tp_name*/
    sizeof(CVesicleModel),             /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)CVesicleModel_dealloc, /*tp_dealloc*/
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
    "CVesicleModel objects",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,		               /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    CVesicleModel_methods,             /* tp_methods */
    CVesicleModel_members,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)CVesicleModel_init,      /* tp_init */
    0,                         /* tp_alloc */
    CVesicleModel_new,                 /* tp_new */
};


//static PyMethodDef module_methods[] = {
//    {NULL} 
//};

/**
 * Function used to add the model class to a module
 * @param module: module to add the class to
 */ 
void addCVesicleModel(PyObject *module) {
	PyObject *d;
	
    if (PyType_Ready(&CVesicleModelType) < 0)
        return;

    Py_INCREF(&CVesicleModelType);
    PyModule_AddObject(module, "CVesicleModel", (PyObject *)&CVesicleModelType);
    
    d = PyModule_GetDict(module);
    CVesicleModelError = PyErr_NewException("CVesicleModel.error", NULL, NULL);
    PyDict_SetItemString(d, "CVesicleModelError", CVesicleModelError);
}

