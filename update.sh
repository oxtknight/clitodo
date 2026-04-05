#!/bin/bash
REPO_PATH="$HOME/.clitodo/repo"
if [ ! -d "$REPO_PATH" ]; then
    echo "Source repo not found at $REPO_PATH"
    exit 1
fi

cd "$REPO_PATH"
echo "Pulling latest changes from the repository..."
git pull origin main
echo "Rebuilding..."
make 
if [ $? -eq 0 ]; then 
    echo "Installing..."
    if [ -n "$TERMUX_VERSION" ]; then
        cp clitodo $PREFIX/bin/
    else
        sudo make install
    fi
    echo "Update complete!"
fi
