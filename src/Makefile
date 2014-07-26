SUBDIRS := shared_lib shared_memory

.PHONY: clean
clean: ${SUBDIRS}
	@echo "Clean..."

.PHONY: ${SUBDIRS}
${SUBDIRS}:
	@echo "Executing make on $@"
	$(MAKE) -C $@ $(TARGET)
#	$(if $(TARGET), $(MAKE) $(TARGET))
