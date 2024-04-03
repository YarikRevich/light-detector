.ONESHELL:

.PHONY: help
.DEFAULT_GOAL := help
help:
	@grep -h -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

.PHONY: clean
clean: ## Cleans generated core files
ifneq (,$(wildcard ./Debug))
	@rm -r ./Debug

	@echo "Debug directory has been successfully deleted"
else
	@echo "Debug directory does not exist"
endif

ifneq (,$(wildcard ./Core/Src/main.c))
	@find ./Core/Src -name "*.cpp" | xargs -I {} rm {}
	@cd ./Core/Src && \
		for file in *; do \
			mv "$$file" "`echo $$file | sed 's/\.c$$/.cpp/'`"; \
		done

	@echo "*.c files rename operation was performed successfully"
else
	@echo "*.c files intented to be renamed don't exist"
endif

prepare: ## Install prerequisites
	pip3 install -r requirements.txt

install: prepare ## Build and install the application
	python3 setup.py install --user

.PHONY: all
all: install