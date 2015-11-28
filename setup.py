from setuptools import setup, Extension

levenshteinpy3 = Extension("levenshteinpy3", sources=["levenshtein.c"])

setup(name = "levenshteinpy3",
		version = '0.1',
		description = 'edit_distance extension for Python',
		ext_modules = [levenshteinpy3])
