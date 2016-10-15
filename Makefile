.PHONY: clean All

All:
	@echo "----------Building project:[ automata - Debug ]----------"
	@cd "automata" && "$(MAKE)" -f  "automata.mk"
clean:
	@echo "----------Cleaning project:[ automata - Debug ]----------"
	@cd "automata" && "$(MAKE)" -f  "automata.mk" clean
