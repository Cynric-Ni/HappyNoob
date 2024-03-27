import sys
from PyInstaller.__main__ import run

if __name__ == '__main__':
    # 配置 PyInstaller 参数
    opts = ['app.py', '--onefile', '--windowed']
    run(opts)