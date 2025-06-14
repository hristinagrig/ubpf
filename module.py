from osv.modules import api
from osv.modules.filemap import FileMap
import os

#this_dir = os.path.dirname(__file__)
#usr_files = FileMap()
#usr_files.add(os.path.join(this_dir, 'prog.o')).to('/prog.o') 

default = api.run('/ubpf.so')