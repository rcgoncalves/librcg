SRC_DIR=src
DXG_CFG=dox
TMP_DIR=tmp
DOCS_DIR=docs

docs : $(wildcard $(DXG_CFG)/*) $(wildcard $(SRC_DIR)/*.[ch])
	mkdir -p $(TMP_DIR)
	doxygen $(DXG_CFG)/Doxyfile > $(TMP_DIR)/doxygen.txt

clean :
	rm -r $(TMP_DIR) $(DOCS_DIR)
