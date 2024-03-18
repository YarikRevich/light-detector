.PHONY: help
.DEFAULT_GOAL := help
help:
	@grep -h -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

.PHONY: generate
generate: ## Generate prerequisites
	@protoc --plugin=/Volumes/Files/embedded/university/techno/project/deps/EmbeddedProto -I./Resources/Proto --eams_out=./Core/External/Proto/Generated test.proto
	@protoc -I./Resources/Proto --python_out=./Scripts/graph/proto test.proto

.PHONY: build
build: ## Build the IOC project
	@cd ./code/go/0chain.net/authorizer/ && go mod download && go mod tidy && CGO_ENABLED=1 go test -v -tags bn256 ./...