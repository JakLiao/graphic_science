由于TC中的graphics.h不是C语言中的标准函数，而是由Borland公司自行开发的，而且是面向DOS的16位，无法直接在VC++中使用；

出于此目的，设计了面向VC++的graphics.h头文件，以及包含一些链接函数的C++程序winbgi.cpp和winbgi.lib；

如何使用？第一种方法——创建工程之后，在Source Files中导入winbgi.cpp文件，在Header Files中导入graphics.h文件，并且将这两个文件和winbgi.lib拷贝至该工程所在的目录下。

第二种方法——添加路径法，选中Tools－Options－Directories，分别在Include Files和Library Files添加图形包winbgi的路径，然后在Source Files中导入winbgi.cpp文件，在Header Files中导入graphics.h文件。