cmake . -B cmbuild -L \
	-DCMAKE_OSX_ARCHITECTURES="x86_64" \
	-DCMAKE_OSX_DEPLOYMENT_TARGET=10.15 \
	-DUSE_MMG=ON \
	-DUSE_LEVMAR=ON \
	-DUSE_HYPRE=ON \
    -DOMP_INC=/Users/gitRunner/local/x86_64/homebrew/opt/libomp/include
