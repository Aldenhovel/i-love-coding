# Cifar 10 & Cifar100

## 简介

The CIFAR-10 and CIFAR-100 are labeled subsets of the [80 million tiny images](http://people.csail.mit.edu/torralba/tinyimages/) dataset. They were collected by Alex Krizhevsky, Vinod Nair, and Geoffrey Hinton.

## The CIFAR-10 dataset

The CIFAR-10 dataset consists of 60000 32x32 colour images in 10 classes, with 6000 images per class. There are 50000 training images and 10000 test images.

The dataset is divided into five training batches and one test batch, each with 10000 images. The test batch contains exactly 1000 randomly-selected images from each class. The training batches contain the remaining images in random order, but some training batches may contain more images from one class than another. Between them, the training batches contain exactly 5000 images from each class.

Here are the classes in the dataset, as well as 10 random images from each:

|            |                                                              |                                                              |                                                              |                                                              |                                                              |                                                              |                                                              |                                                              |                                                              |                                                              |
| ---------- | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| airplane   | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/airplane1.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/airplane2.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/airplane3.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/airplane4.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/airplane5.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/airplane6.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/airplane7.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/airplane8.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/airplane9.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/airplane10.png) |
| automobile | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/automobile1.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/automobile2.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/automobile3.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/automobile4.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/automobile5.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/automobile6.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/automobile7.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/automobile8.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/automobile9.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/automobile10.png) |
| bird       | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/bird1.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/bird2.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/bird3.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/bird4.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/bird5.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/bird6.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/bird7.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/bird8.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/bird9.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/bird10.png) |
| cat        | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/cat1.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/cat2.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/cat3.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/cat4.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/cat5.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/cat6.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/cat7.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/cat8.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/cat9.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/cat10.png) |
| deer       | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/deer1.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/deer2.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/deer3.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/deer4.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/deer5.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/deer6.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/deer7.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/deer8.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/deer9.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/deer10.png) |
| dog        | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/dog1.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/dog2.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/dog3.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/dog4.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/dog5.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/dog6.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/dog7.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/dog8.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/dog9.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/dog10.png) |
| frog       | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/frog1.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/frog2.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/frog3.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/frog4.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/frog5.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/frog6.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/frog7.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/frog8.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/frog9.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/frog10.png) |
| horse      | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/horse1.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/horse2.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/horse3.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/horse4.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/horse5.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/horse6.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/horse7.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/horse8.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/horse9.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/horse10.png) |
| ship       | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/ship1.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/ship2.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/ship3.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/ship4.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/ship5.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/ship6.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/ship7.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/ship8.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/ship9.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/ship10.png) |
| truck      | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/truck1.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/truck2.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/truck3.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/truck4.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/truck5.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/truck6.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/truck7.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/truck8.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/truck9.png) | ![img](https://www.cs.toronto.edu/~kriz/cifar-10-sample/truck10.png) |


The classes are completely mutually exclusive. There is no overlap between automobiles and trucks. "Automobile" includes sedans, SUVs, things of that sort. "Truck" includes only big trucks. Neither includes pickup trucks.

## 下载

https://www.cs.toronto.edu/~kriz/cifar.html
