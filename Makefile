all:
	python setup.py develop
	python test.py

clean:
	rm -rf build levenshtein.egg-info levenshtein.so
