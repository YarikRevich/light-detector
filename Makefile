.ONESHELL:

.PHONY: help
.DEFAULT_GOAL := help
help:
	@grep -h -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

.PHONY: clean
clean: ## Cleans generated core files
ifneq ("$(wildcard $(./Debug))","")
	@rm -r ./Debug
else
	@echo "Debug directory does not exist"
endif

ifneq ("$(wildcard $(./Core/Src/main.c))","")
    @cd ./Core/Src && \
    		@find . -name "*.cpp" | xargs -I {} rm {} \
            for file in *; do \
                mv "$$file" "`echo $$file | sed 's/\.c$$/.cpp/'`"; \
            done
else
	@echo "*.c files intented to be renamed don't exist"
endif

.PHONY: generate
generate: ## Generate prerequisites
	@protoc --plugin=/Volumes/Files/embedded/university/techno/project/deps/EmbeddedProto -I./Resources/Proto --eams_out=./Core/External/Proto/Generated test.proto
	@protoc -I./Resources/Proto --python_out=./Scripts/graph/proto test.proto

.PHONY: build
build: ## Build the IOC project
	@cd ./code/go/0chain.net/authorizer/ && go mod download && go mod tidy && CGO_ENABLED=1 go test -v -tags bn256 ./...