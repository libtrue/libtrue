from setuptools import setup

setup(
    name = "py-libtrue",
    version = "0.0.1",
    author = "Matt Joras",
    author_email = "matt.joras@gmail.com",
    description = "Python bindings for libtrue.",
    license = "BSD",
    url = "https://github.com/zxombie/libtrue",
    packages=['true'],
    classifiers=[
        "License :: OSI Approved :: BSD License",
    ],
    setup_requires=["cffi>=1.0.0"],
    cffi_modules=["libtrue_build.py:ffi"],
    install_requires=["cffi>=1.0.0"],
)
