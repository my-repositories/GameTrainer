from sys import path, argv
path.append('cpp-coveralls')

#from urllib3.exceptions import InsecureRequestWarning
#requests.packages.urllib3.disable_warnings(category=InsecureRequestWarning)

from cpp_coveralls.__init__ import run
run()
