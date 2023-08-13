#================================[[ beg-code ]]================================#



#===(manditory)============================================#
# basename of executable, header, and all code files
NAME_BASE  = yVIEW
# additional standard and outside libraries
LIB_STD    = -lm
# all heatherly libraries used, debug versions whenever available
LIB_MINE   = -lySTR_debug   -lyVIHUB_debug -lyMODE_debug -lyKEYS_debug -lyPARSE_debug
# directory for production code, no trailing slash
INST_DIR   = 



#===(optional)=============================================#
# extra include directories required
INC_MINE   = 
# utilities generated, separate from main program
NAME_UTIL  = 
# libraries only for the utilities
LIB_UTIL   = 



#===(post-processing)======================================#
# create a rule for...
#install_prep       :
#remove_prep        :



#===(master template)======================================#
include /usr/local/sbin/make_program



#===(post-processing)======================================#
# create a rule for...
#install_post       :
#remove_post        :

man_post           :
	cp -f /usr/local/man/man6/yVIEW_note.6.bz2 /usr/local/man/man6/:note.6.bz2
	printf "installing alternate manual name\n"


#================================[[ end-code ]]================================#
