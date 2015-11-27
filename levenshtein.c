#include <python2.7/Python.h>

static int min(int * values, int length){
	int i;
	int minval = INT_MAX;
	for(i=0; i<length; i++){
		if(values[i] < minval){
			minval = values[i];		
		}
	}
	return minval;
}

static int edit_distance(char * worda, char * wordb, int i, int j){
	int triad[3];
	if(i==0 && j==0)
		return 0;
	if(i==0)
		return j;
	if(j==0)
		return i;
	if(worda[i-1] == wordb[j-1])
		return edit_distance(worda, wordb, i-1, j-1);
	triad[0] = edit_distance(worda, wordb, i-1, j);
	triad[1] = edit_distance(worda, wordb, i, j-1);
	triad[2] = edit_distance(worda, wordb, i-1, j-1);
	return min(triad, 3) + 1;
}

int ParseArgsMakeComparisons(int array[], Py_ssize_t array_size, Py_ssize_t args_size, PyObject *args) {
	Py_ssize_t i; /*index of current word*/
	Py_ssize_t j; /*index of word we compare current word to, should be subsequent to current word*/
	Py_ssize_t k=0; /*current index in array*/
	PyObject *temp_p1, *temp_p2;
	char *word1, *word2;
	
	for (i=0;i<args_size;i++) {
		
		temp_p1 = PyTuple_GetItem(args,i);
		
		word1 = PyString_AsString(temp_p1);
		printf("word1 %s\n", word1);
		for (j=i+1;j<args_size;j++) {
			temp_p2 = PyTuple_GetItem(args,j);
			word2 = PyString_AsString(temp_p2);
			printf("word2 %s\n", word2);
			array[k] = edit_distance(word1, word2, strlen(word1), strlen(word2));
			k++;
			//Py_DECREF(temp_p2);
			//Py_DECREF(word2);
		}
		//Py_DECREF(temp_p1);
		//Py_DECREF(word1);
	}
	
	return 1;
}

PyObject *PyMultiVarEditDistance(PyObject *self, PyObject *args) {

	Py_ssize_t num_words = PyTuple_Size(args);


	// if (num_words < 2) {
	// 	if(!PyErr_Occurred()) 
 //            PyErr_SetString(PyExc_TypeError,"You must supply at least two arguments.");
 //        return NULL;
	// }

	Py_ssize_t num_comparisons = num_words * (num_words-1) / 2;
	int *comparisons = malloc(num_comparisons * sizeof(int));
	PyObject *comparison_distances_list_out;
	if (!(ParseArgsMakeComparisons(comparisons, num_comparisons, num_words, args))) { 
        free(comparisons);
        return NULL;
    }
    
    int i; 

    comparison_distances_list_out = PyList_New(num_comparisons);
    
    for (i=0;i<num_comparisons;i++) {
    	PyList_SET_ITEM(comparison_distances_list_out, i, PyInt_FromLong(comparisons[i]));
    	
    }
    free(comparisons);
    return (PyObject *) comparison_distances_list_out;
	
	return NULL;
}

PyObject *PyEditDistance(PyObject *self, PyObject *args){
	char * worda, * wordb;
	int distance;

	if(PyArg_ParseTuple(args, "ss", &worda, &wordb)){
		distance = edit_distance(worda, wordb, 
						strlen(worda), strlen(wordb));
		return Py_BuildValue("i", distance);
	}

	return NULL;
    
}

PyObject *PyMultiEditDistance(PyObject *self, PyObject *args){
	char * worda, * wordb, * wordc;
	int distance1, distance2, distance3;

	if(PyArg_ParseTuple(args, "sss", &worda, &wordb, &wordc)){
		distance1 = edit_distance(worda, wordb, 
						strlen(worda), strlen(wordb));
        distance2 = edit_distance(worda, wordc, 
						strlen(worda), strlen(wordc));
        distance3 = edit_distance(wordb, wordc, 
						strlen(wordb), strlen(wordc));
		return Py_BuildValue("[iii]", distance1, distance2, distance3);
	}

	return NULL;
    
}

PyObject *PyMultiEditDistance4(PyObject *self, PyObject *args){
	char * worda, * wordb, * wordc, * wordd;
	int distance1, distance2, distance3, distance4, distance5, distance6;

	if(PyArg_ParseTuple(args, "ssss", &worda, &wordb, &wordc, &wordd)){
		distance1 = edit_distance(worda, wordb, 
						strlen(worda), strlen(wordb));
        distance2 = edit_distance(worda, wordc, 
						strlen(worda), strlen(wordc));
        distance3 = edit_distance(worda, wordd, 
						strlen(worda), strlen(wordd));
        distance4 = edit_distance(wordb, wordc, 
						strlen(wordb), strlen(wordc));
        distance5 = edit_distance(wordb, wordd, 
						strlen(wordb), strlen(wordd));
        distance6 = edit_distance(wordc, wordd, 
						strlen(wordc), strlen(wordd));
        
		return Py_BuildValue("[iiiiii]", distance1,distance2,distance3,distance4,distance5,distance6);
	}

	return NULL;
    
}

PyMethodDef methods[] = {
	{"edit_distance", PyEditDistance},
    {"multi_edit_distance", PyMultiEditDistance},
    {"multi_edit_distance4", PyMultiEditDistance4},
    {"multi_var_edit_distance", PyMultiVarEditDistance},
    {NULL, NULL},
};

void initlevenshtein(){
	PyObject *m;

	m = Py_InitModule("levenshtein", methods);
	if(m==NULL) return;

}


