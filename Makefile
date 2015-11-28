all:
	python setup.py develop
	python test.py

clean:
	rm -rf build levenshteinpy3.egg-info levenshteinpy3.so levenshteinpy3.cpython-34m.so 
