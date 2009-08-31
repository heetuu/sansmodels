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

/** CStackedDisksModel
 *
 * C extension 
 *
 * WARNING: THIS FILE WAS GENERATED BY WRAPPERGENERATOR.PY
 *          DO NOT MODIFY THIS FILE, MODIFY stacked_disks.h
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
#include "stacked_disks.h"
}

#include "models.hh"
#include "dispersion_visitor.hh"

/// Error object for raised exceptions
static PyObject * CStackedDisksModelError = NULL;


// Class definition
typedef struct {
    PyObject_HEAD
    /// Parameters
    PyObject * params;
    /// Dispersion parameters
    PyObject * dispersion;
    /// Underlying model object
    StackedDisksModel * model;
    /// Log for unit testing
    PyObject * log;
} CStackedDisksModel;


static void
CStackedDisksModel_dealloc(CStackedDisksModel* self)
{
    self->ob_type->tp_free((PyObject*)self);
    

}

static PyObject *
CStackedDisksModel_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    CStackedDisksModel *self;
    
    self = (CStackedDisksModel *)type->tp_alloc(type, 0);
   
    return (PyObject *)self;
}

static int
CStackedDisksModel_init(CStackedDisksModel *self, PyObject *args, PyObject *kwds)
{
    if (self != NULL) {
    	
    	// Create parameters
        self->params = PyDict_New();
        self->dispersion = PyDict_New();
        self->model = new StackedDisksModel();
        
        // Initialize parameter dictionary
        PyDict_SetItemString(self->params,"core_sld",Py_BuildValue("d",0.000004));
        PyDict_SetItemString(self->params,"core_thick",Py_BuildValue("d",10.000000));
        PyDict_SetItemString(self->params,"layer_thick",Py_BuildValue("d",15.000000));
        PyDict_SetItemString(self->params,"axis_theta",Py_BuildValue("d",0.000000));
        PyDict_SetItemString(self->params,"layer_sld",Py_BuildValue("d",-0.000000));
        PyDict_SetItemString(self->params,"axis_phi",Py_BuildValue("d",0.000000));
        PyDict_SetItemString(self->params,"solvent_sld",Py_BuildValue("d",0.000005));
        PyDict_SetItemString(self->params,"scale",Py_BuildValue("d",0.010000));
        PyDict_SetItemString(self->params,"radius",Py_BuildValue("d",3000.000000));
        PyDict_SetItemString(self->params,"background",Py_BuildValue("d",0.001000));
        PyDict_SetItemString(self->params,"sigma_d",Py_BuildValue("d",0.000000));
        PyDict_SetItemString(self->params,"n_stacking",Py_BuildValue("d",1.000000));
        // Initialize dispersion / averaging parameter dict
        DispersionVisitor* visitor = new DispersionVisitor();
        PyObject * disp_dict;
        disp_dict = PyDict_New();
        self->model->core_thick.dispersion->accept_as_source(visitor, self->model->core_thick.dispersion, disp_dict);
        PyDict_SetItemString(self->dispersion, "core_thick", disp_dict);
        disp_dict = PyDict_New();
        self->model->layer_thick.dispersion->accept_as_source(visitor, self->model->layer_thick.dispersion, disp_dict);
        PyDict_SetItemString(self->dispersion, "layer_thick", disp_dict);
        disp_dict = PyDict_New();
        self->model->radius.dispersion->accept_as_source(visitor, self->model->radius.dispersion, disp_dict);
        PyDict_SetItemString(self->dispersion, "radius", disp_dict);
        disp_dict = PyDict_New();
        self->model->axis_theta.dispersion->accept_as_source(visitor, self->model->axis_theta.dispersion, disp_dict);
        PyDict_SetItemString(self->dispersion, "axis_theta", disp_dict);
        disp_dict = PyDict_New();
        self->model->axis_phi.dispersion->accept_as_source(visitor, self->model->axis_phi.dispersion, disp_dict);
        PyDict_SetItemString(self->dispersion, "axis_phi", disp_dict);


         
        // Create empty log
        self->log = PyDict_New();
        
        

    }
    return 0;
}

static PyMemberDef CStackedDisksModel_members[] = {
    {"params", T_OBJECT, offsetof(CStackedDisksModel, params), 0,
     "Parameters"},
	{"dispersion", T_OBJECT, offsetof(CStackedDisksModel, dispersion), 0,
	  "Dispersion parameters"},     
    {"log", T_OBJECT, offsetof(CStackedDisksModel, log), 0,
     "Log"},
    {NULL}  /* Sentinel */
};

/** Read double from PyObject
    @param p PyObject
    @return double
*/
double CStackedDisksModel_readDouble(PyObject *p) {
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
 
static PyObject *evaluateOneDim(StackedDisksModel* model, PyArrayObject *q){
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
 static PyObject * evaluateTwoDimXY( StackedDisksModel* model, 
                              PyArrayObject *x, PyArrayObject *y)
 {
    PyArrayObject *result;
    int i,j, x_len, y_len, dims[2];
    //check validity of input vectors
    if (x->nd != 2 || x->descr->type_num != PyArray_DOUBLE
        || y->nd != 2 || y->descr->type_num != PyArray_DOUBLE
        || y->dimensions[1] != x->dimensions[0]){
        const char * message= "evaluateTwoDimXY  expect 2 numpy arrays";
        PyErr_SetString(PyExc_ValueError , message); 
        return NULL;
    }
   
	if (PyArray_Check(x) && PyArray_Check(y)) {
		
	    x_len = dims[1]= x->dimensions[0];
        y_len = dims[0]= y->dimensions[1];
	    
	    // Make a new double matrix of same dims
        result=(PyArrayObject *) PyArray_FromDims(2,dims,NPY_DOUBLE);
        if (result == NULL){
	    const char * message= "Could not create result ";
        PyErr_SetString(PyExc_RuntimeError , message);
	    return NULL;
	    }
       
        /* Do the calculation. */
        for ( j=0; j< y_len; j++) {
            for ( i=0; i< x_len; i++) {
                double x_value = *(double *)(x->data + i*x->strides[0]);
      		    double y_value = *(double *)(y->data + j*y->strides[1]);
      			double *result_value = (double *)(result->data +
      			      j*result->strides[0] + i*result->strides[1]);
      			*result_value = (*model)(x_value, y_value);
            }           
        }
        return PyArray_Return(result); 
        
        }else{
		    PyErr_SetString(CStackedDisksModelError, 
                   "CStackedDisksModel.evaluateTwoDimXY couldn't run.");
	        return NULL;
		}      	
}
/**
 *  evalDistribution function evaluate a model function with input vector
 *  @param args: input q as vector or [qx, qy] where qx, qy are vectors
 *
 */ 
static PyObject * evalDistribution(CStackedDisksModel *self, PyObject *args){
	PyObject *qx, *qy;
	PyArrayObject * pars;
	int npars ,mpars;
	
	// Get parameters
	
	    // Reader parameter dictionary
    self->model->core_sld = PyFloat_AsDouble( PyDict_GetItemString(self->params, "core_sld") );
    self->model->core_thick = PyFloat_AsDouble( PyDict_GetItemString(self->params, "core_thick") );
    self->model->layer_thick = PyFloat_AsDouble( PyDict_GetItemString(self->params, "layer_thick") );
    self->model->axis_theta = PyFloat_AsDouble( PyDict_GetItemString(self->params, "axis_theta") );
    self->model->layer_sld = PyFloat_AsDouble( PyDict_GetItemString(self->params, "layer_sld") );
    self->model->axis_phi = PyFloat_AsDouble( PyDict_GetItemString(self->params, "axis_phi") );
    self->model->solvent_sld = PyFloat_AsDouble( PyDict_GetItemString(self->params, "solvent_sld") );
    self->model->scale = PyFloat_AsDouble( PyDict_GetItemString(self->params, "scale") );
    self->model->radius = PyFloat_AsDouble( PyDict_GetItemString(self->params, "radius") );
    self->model->background = PyFloat_AsDouble( PyDict_GetItemString(self->params, "background") );
    self->model->sigma_d = PyFloat_AsDouble( PyDict_GetItemString(self->params, "sigma_d") );
    self->model->n_stacking = PyFloat_AsDouble( PyDict_GetItemString(self->params, "n_stacking") );
    // Read in dispersion parameters
    PyObject* disp_dict;
    DispersionVisitor* visitor = new DispersionVisitor();
    disp_dict = PyDict_GetItemString(self->dispersion, "core_thick");
    self->model->core_thick.dispersion->accept_as_destination(visitor, self->model->core_thick.dispersion, disp_dict);
    disp_dict = PyDict_GetItemString(self->dispersion, "layer_thick");
    self->model->layer_thick.dispersion->accept_as_destination(visitor, self->model->layer_thick.dispersion, disp_dict);
    disp_dict = PyDict_GetItemString(self->dispersion, "radius");
    self->model->radius.dispersion->accept_as_destination(visitor, self->model->radius.dispersion, disp_dict);
    disp_dict = PyDict_GetItemString(self->dispersion, "axis_theta");
    self->model->axis_theta.dispersion->accept_as_destination(visitor, self->model->axis_theta.dispersion, disp_dict);
    disp_dict = PyDict_GetItemString(self->dispersion, "axis_phi");
    self->model->axis_phi.dispersion->accept_as_destination(visitor, self->model->axis_phi.dispersion, disp_dict);

	
	// Get input and determine whether we have to supply a 1D or 2D return value.
	if ( !PyArg_ParseTuple(args,"O",&pars) ) {
	    PyErr_SetString(CStackedDisksModelError, 
	    	"CStackedDisksModel.evalDistribution expects a q value.");
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
		    PyErr_SetString(CStackedDisksModelError, 
                   "CStackedDisksModel.evalDistribution expect numpy array of one dimension.");
	        return NULL;
		}
    }else if( PyList_Check(pars)==1) {
    	// Length of list should be 2 for I(qx,qy)
	    mpars = PyList_GET_SIZE(pars); 
	    if(mpars!=2) {
	    	PyErr_SetString(CStackedDisksModelError, 
	    		"CStackedDisksModel.evalDistribution expects a list of dimension 2.");
	    	return NULL;
	    }
	     qx = PyList_GET_ITEM(pars,0);
	     qy = PyList_GET_ITEM(pars,1);
	     if (PyArray_Check(qx) && PyArray_Check(qy)) {
	         return evaluateTwoDimXY(self->model, (PyArrayObject*)qx,
		           (PyArrayObject*)qy);
		 }else{
		    PyErr_SetString(CStackedDisksModelError, 
                   "CStackedDisksModel.evalDistribution expect 2 numpy arrays in list.");
	        return NULL;
	     }
	}
	PyErr_SetString(CStackedDisksModelError, 
                   "CStackedDisksModel.evalDistribution couln't be run.");
	return NULL;
	
}

/**
 * Function to call to evaluate model
 * @param args: input q or [q,phi]
 * @return: function value
 */
static PyObject * run(CStackedDisksModel *self, PyObject *args) {
	double q_value, phi_value;
	PyObject* pars;
	int npars;
	
	// Get parameters
	
	    // Reader parameter dictionary
    self->model->core_sld = PyFloat_AsDouble( PyDict_GetItemString(self->params, "core_sld") );
    self->model->core_thick = PyFloat_AsDouble( PyDict_GetItemString(self->params, "core_thick") );
    self->model->layer_thick = PyFloat_AsDouble( PyDict_GetItemString(self->params, "layer_thick") );
    self->model->axis_theta = PyFloat_AsDouble( PyDict_GetItemString(self->params, "axis_theta") );
    self->model->layer_sld = PyFloat_AsDouble( PyDict_GetItemString(self->params, "layer_sld") );
    self->model->axis_phi = PyFloat_AsDouble( PyDict_GetItemString(self->params, "axis_phi") );
    self->model->solvent_sld = PyFloat_AsDouble( PyDict_GetItemString(self->params, "solvent_sld") );
    self->model->scale = PyFloat_AsDouble( PyDict_GetItemString(self->params, "scale") );
    self->model->radius = PyFloat_AsDouble( PyDict_GetItemString(self->params, "radius") );
    self->model->background = PyFloat_AsDouble( PyDict_GetItemString(self->params, "background") );
    self->model->sigma_d = PyFloat_AsDouble( PyDict_GetItemString(self->params, "sigma_d") );
    self->model->n_stacking = PyFloat_AsDouble( PyDict_GetItemString(self->params, "n_stacking") );
    // Read in dispersion parameters
    PyObject* disp_dict;
    DispersionVisitor* visitor = new DispersionVisitor();
    disp_dict = PyDict_GetItemString(self->dispersion, "core_thick");
    self->model->core_thick.dispersion->accept_as_destination(visitor, self->model->core_thick.dispersion, disp_dict);
    disp_dict = PyDict_GetItemString(self->dispersion, "layer_thick");
    self->model->layer_thick.dispersion->accept_as_destination(visitor, self->model->layer_thick.dispersion, disp_dict);
    disp_dict = PyDict_GetItemString(self->dispersion, "radius");
    self->model->radius.dispersion->accept_as_destination(visitor, self->model->radius.dispersion, disp_dict);
    disp_dict = PyDict_GetItemString(self->dispersion, "axis_theta");
    self->model->axis_theta.dispersion->accept_as_destination(visitor, self->model->axis_theta.dispersion, disp_dict);
    disp_dict = PyDict_GetItemString(self->dispersion, "axis_phi");
    self->model->axis_phi.dispersion->accept_as_destination(visitor, self->model->axis_phi.dispersion, disp_dict);

	
	// Get input and determine whether we have to supply a 1D or 2D return value.
	if ( !PyArg_ParseTuple(args,"O",&pars) ) {
	    PyErr_SetString(CStackedDisksModelError, 
	    	"CStackedDisksModel.run expects a q value.");
		return NULL;
	}
	  
	// Check params
	if( PyList_Check(pars)==1) {
		
		// Length of list should be 2 for I(q,phi)
	    npars = PyList_GET_SIZE(pars); 
	    if(npars!=2) {
	    	PyErr_SetString(CStackedDisksModelError, 
	    		"CStackedDisksModel.run expects a double or a list of dimension 2.");
	    	return NULL;
	    }
	    // We have a vector q, get the q and phi values at which
	    // to evaluate I(q,phi)
	    q_value = CStackedDisksModel_readDouble(PyList_GET_ITEM(pars,0));
	    phi_value = CStackedDisksModel_readDouble(PyList_GET_ITEM(pars,1));
	    // Skip zero
	    if (q_value==0) {
	    	return Py_BuildValue("d",0.0);
	    }
		return Py_BuildValue("d",(*(self->model)).evaluate_rphi(q_value,phi_value));

	} else {

		// We have a scalar q, we will evaluate I(q)
		q_value = CStackedDisksModel_readDouble(pars);		
		
		return Py_BuildValue("d",(*(self->model))(q_value));
	}	
}
/**
 * Function to call to calculate_ER
 * @return: effective radius value 
 */
static PyObject * calculate_ER(CStackedDisksModel *self) {

	PyObject* pars;
	int npars;
	
	// Get parameters
	
	    // Reader parameter dictionary
    self->model->core_sld = PyFloat_AsDouble( PyDict_GetItemString(self->params, "core_sld") );
    self->model->core_thick = PyFloat_AsDouble( PyDict_GetItemString(self->params, "core_thick") );
    self->model->layer_thick = PyFloat_AsDouble( PyDict_GetItemString(self->params, "layer_thick") );
    self->model->axis_theta = PyFloat_AsDouble( PyDict_GetItemString(self->params, "axis_theta") );
    self->model->layer_sld = PyFloat_AsDouble( PyDict_GetItemString(self->params, "layer_sld") );
    self->model->axis_phi = PyFloat_AsDouble( PyDict_GetItemString(self->params, "axis_phi") );
    self->model->solvent_sld = PyFloat_AsDouble( PyDict_GetItemString(self->params, "solvent_sld") );
    self->model->scale = PyFloat_AsDouble( PyDict_GetItemString(self->params, "scale") );
    self->model->radius = PyFloat_AsDouble( PyDict_GetItemString(self->params, "radius") );
    self->model->background = PyFloat_AsDouble( PyDict_GetItemString(self->params, "background") );
    self->model->sigma_d = PyFloat_AsDouble( PyDict_GetItemString(self->params, "sigma_d") );
    self->model->n_stacking = PyFloat_AsDouble( PyDict_GetItemString(self->params, "n_stacking") );
    // Read in dispersion parameters
    PyObject* disp_dict;
    DispersionVisitor* visitor = new DispersionVisitor();
    disp_dict = PyDict_GetItemString(self->dispersion, "core_thick");
    self->model->core_thick.dispersion->accept_as_destination(visitor, self->model->core_thick.dispersion, disp_dict);
    disp_dict = PyDict_GetItemString(self->dispersion, "layer_thick");
    self->model->layer_thick.dispersion->accept_as_destination(visitor, self->model->layer_thick.dispersion, disp_dict);
    disp_dict = PyDict_GetItemString(self->dispersion, "radius");
    self->model->radius.dispersion->accept_as_destination(visitor, self->model->radius.dispersion, disp_dict);
    disp_dict = PyDict_GetItemString(self->dispersion, "axis_theta");
    self->model->axis_theta.dispersion->accept_as_destination(visitor, self->model->axis_theta.dispersion, disp_dict);
    disp_dict = PyDict_GetItemString(self->dispersion, "axis_phi");
    self->model->axis_phi.dispersion->accept_as_destination(visitor, self->model->axis_phi.dispersion, disp_dict);

		
	return Py_BuildValue("d",(*(self->model)).calculate_ER());

}
/**
 * Function to call to evaluate model in cartesian coordinates
 * @param args: input q or [qx, qy]]
 * @return: function value
 */
static PyObject * runXY(CStackedDisksModel *self, PyObject *args) {
	double qx_value, qy_value;
	PyObject* pars;
	int npars;
	
	// Get parameters
	
	    // Reader parameter dictionary
    self->model->core_sld = PyFloat_AsDouble( PyDict_GetItemString(self->params, "core_sld") );
    self->model->core_thick = PyFloat_AsDouble( PyDict_GetItemString(self->params, "core_thick") );
    self->model->layer_thick = PyFloat_AsDouble( PyDict_GetItemString(self->params, "layer_thick") );
    self->model->axis_theta = PyFloat_AsDouble( PyDict_GetItemString(self->params, "axis_theta") );
    self->model->layer_sld = PyFloat_AsDouble( PyDict_GetItemString(self->params, "layer_sld") );
    self->model->axis_phi = PyFloat_AsDouble( PyDict_GetItemString(self->params, "axis_phi") );
    self->model->solvent_sld = PyFloat_AsDouble( PyDict_GetItemString(self->params, "solvent_sld") );
    self->model->scale = PyFloat_AsDouble( PyDict_GetItemString(self->params, "scale") );
    self->model->radius = PyFloat_AsDouble( PyDict_GetItemString(self->params, "radius") );
    self->model->background = PyFloat_AsDouble( PyDict_GetItemString(self->params, "background") );
    self->model->sigma_d = PyFloat_AsDouble( PyDict_GetItemString(self->params, "sigma_d") );
    self->model->n_stacking = PyFloat_AsDouble( PyDict_GetItemString(self->params, "n_stacking") );
    // Read in dispersion parameters
    PyObject* disp_dict;
    DispersionVisitor* visitor = new DispersionVisitor();
    disp_dict = PyDict_GetItemString(self->dispersion, "core_thick");
    self->model->core_thick.dispersion->accept_as_destination(visitor, self->model->core_thick.dispersion, disp_dict);
    disp_dict = PyDict_GetItemString(self->dispersion, "layer_thick");
    self->model->layer_thick.dispersion->accept_as_destination(visitor, self->model->layer_thick.dispersion, disp_dict);
    disp_dict = PyDict_GetItemString(self->dispersion, "radius");
    self->model->radius.dispersion->accept_as_destination(visitor, self->model->radius.dispersion, disp_dict);
    disp_dict = PyDict_GetItemString(self->dispersion, "axis_theta");
    self->model->axis_theta.dispersion->accept_as_destination(visitor, self->model->axis_theta.dispersion, disp_dict);
    disp_dict = PyDict_GetItemString(self->dispersion, "axis_phi");
    self->model->axis_phi.dispersion->accept_as_destination(visitor, self->model->axis_phi.dispersion, disp_dict);

	
	// Get input and determine whether we have to supply a 1D or 2D return value.
	if ( !PyArg_ParseTuple(args,"O",&pars) ) {
	    PyErr_SetString(CStackedDisksModelError, 
	    	"CStackedDisksModel.run expects a q value.");
		return NULL;
	}
	  
	// Check params
	if( PyList_Check(pars)==1) {
		
		// Length of list should be 2 for I(qx, qy))
	    npars = PyList_GET_SIZE(pars); 
	    if(npars!=2) {
	    	PyErr_SetString(CStackedDisksModelError, 
	    		"CStackedDisksModel.run expects a double or a list of dimension 2.");
	    	return NULL;
	    }
	    // We have a vector q, get the qx and qy values at which
	    // to evaluate I(qx,qy)
	    qx_value = CStackedDisksModel_readDouble(PyList_GET_ITEM(pars,0));
	    qy_value = CStackedDisksModel_readDouble(PyList_GET_ITEM(pars,1));
	    return Py_BuildValue("d",(*(self->model))(qx_value,qy_value));

	} else {

		// We have a scalar q, we will evaluate I(q)
		qx_value = CStackedDisksModel_readDouble(pars);		
		
		return Py_BuildValue("d",(*(self->model))(qx_value));
	}	
}

static PyObject * reset(CStackedDisksModel *self, PyObject *args) {
    

    return Py_BuildValue("d",0.0);
}

static PyObject * set_dispersion(CStackedDisksModel *self, PyObject *args) {
	PyObject * disp;
	const char * par_name;

	if ( !PyArg_ParseTuple(args,"sO", &par_name, &disp) ) {
	    PyErr_SetString(CStackedDisksModelError,
	    	"CStackedDisksModel.set_dispersion expects a DispersionModel object.");
		return NULL;
	}
	void *temp = PyCObject_AsVoidPtr(disp);
	DispersionModel * dispersion = static_cast<DispersionModel *>(temp);


	// Ugliness necessary to go from python to C
	    // TODO: refactor this
    if (!strcmp(par_name, "core_thick")) {
        self->model->core_thick.dispersion = dispersion;
    } else    if (!strcmp(par_name, "layer_thick")) {
        self->model->layer_thick.dispersion = dispersion;
    } else    if (!strcmp(par_name, "radius")) {
        self->model->radius.dispersion = dispersion;
    } else    if (!strcmp(par_name, "axis_theta")) {
        self->model->axis_theta.dispersion = dispersion;
    } else    if (!strcmp(par_name, "axis_phi")) {
        self->model->axis_phi.dispersion = dispersion;
    } else {
	    PyErr_SetString(CStackedDisksModelError,
	    	"CStackedDisksModel.set_dispersion expects a valid parameter name.");
		return NULL;
	}

	DispersionVisitor* visitor = new DispersionVisitor();
	PyObject * disp_dict = PyDict_New();
	dispersion->accept_as_source(visitor, dispersion, disp_dict);
	PyDict_SetItemString(self->dispersion, par_name, disp_dict);
    return Py_BuildValue("i",1);
}


static PyMethodDef CStackedDisksModel_methods[] = {
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

static PyTypeObject CStackedDisksModelType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "CStackedDisksModel",             /*tp_name*/
    sizeof(CStackedDisksModel),             /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)CStackedDisksModel_dealloc, /*tp_dealloc*/
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
    "CStackedDisksModel objects",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,		               /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    CStackedDisksModel_methods,             /* tp_methods */
    CStackedDisksModel_members,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)CStackedDisksModel_init,      /* tp_init */
    0,                         /* tp_alloc */
    CStackedDisksModel_new,                 /* tp_new */
};


//static PyMethodDef module_methods[] = {
//    {NULL} 
//};

/**
 * Function used to add the model class to a module
 * @param module: module to add the class to
 */ 
void addCStackedDisksModel(PyObject *module) {
	PyObject *d;
	
    if (PyType_Ready(&CStackedDisksModelType) < 0)
        return;

    Py_INCREF(&CStackedDisksModelType);
    PyModule_AddObject(module, "CStackedDisksModel", (PyObject *)&CStackedDisksModelType);
    
    d = PyModule_GetDict(module);
    CStackedDisksModelError = PyErr_NewException("CStackedDisksModel.error", NULL, NULL);
    PyDict_SetItemString(d, "CStackedDisksModelError", CStackedDisksModelError);
}

