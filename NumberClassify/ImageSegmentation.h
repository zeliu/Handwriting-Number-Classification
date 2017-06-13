#ifndef IMAGESEGMENTATION_H
#define IMAGESEGMENTATION_H

#include "CImg.h"
#include <vector>
#include <list>
#include <iostream>
using namespace std;
using namespace cimg_library;

#define BinaryGap 135
#define BoundaryRemoveGap 7
#define Infinite 249480

#define SingleNumberImgBoundary 5

struct PointPos {
	int x;
	int y;
	PointPos() : x(-1), y(-1) {}
	PointPos(int posX, int posY) : x(posX), y(posY) {}
};

class ImageSegmentation {
public:
	ImageSegmentation(const CImg<int>& _SrcImg);
	~ImageSegmentation();

	void processBinaryImage(bool doDilationY);    //�����ɶ�ֵͼ��
	CImg<int> getBinaryImage();                   //��ȡ��ֵͼ��

	void numberSegmentationMainProcess();         //���������ַ�����
	CImg<int> getHistogramImage();                //��ȡy�����ֱ��ͼ
	CImg<int> getImageWithDividingLine();         //��ȡ�������ߵĶ�ֵͼ
	CImg<int> getColoredNumberDividedImg();       //��ȡ���ֳɲ�ͬ��ɫ���ַ�ͼƬ
	CImg<int> getNumberDividedCircledImg();       //��ȡ�����ÿ��ָ��ͼƬ

	void saveSingleNumberImage(const string baseAddress);

private:
	//��y�����ֱ��ͼ���ҵ�������֮��ķָ���
	void findDividingLine();

	//ͨ���ָ��ߣ���ͼƬ����Ϊһ���е�����
	void divideIntoBarItemImg();

	//��ͨ�������㷨
	void connectedRegionsTagging();
	void connectedRegionsTaggingOfBarItemImg(int barItemIndex);

	//�����µ���tag
	void addNewClass(int x, int y, int barItemIndex);

	//�����ϡ����ϡ����С��������ĸ��ڵ����ҵ���С��tag
	void findMinTag(int x, int y, int &minTag, PointPos &minTagPointPos, int barItemIndex);

	//�ϲ�ĳ����(x,y)�������
	void mergeTagImageAndList(int x, int y, const int minTag, const PointPos minTagPointPos, int barItemIndex);

	//��ȡ�������ֵİ�Χ��
	void getBoundingOfSingleNum(int listIndex, int& xMin, int& xMax, int& yMin, int& yMax);

private:
	CImg<int> SrcGrayImg, BinaryImg, TagImage, HistogramImage, DividingImg;
	vector<CImg<int>> subImageSet;     //һ��������ͼ��
	int imgW, imgH;

	vector<int> inflectionPointSet;    //�յ�
	vector<int> divideLinePointSet;    //ֱ��ͼ��ֵ�����ߵ㼯

	int tagAccumulate = -1;            //���tag�ۼ�ֵ

	vector<int> classTagSet;                   //���tag�б�
	vector<list<PointPos>> pointPosListSet;    //װ�����tag��Ӧ�����е��λ�õ�list���б�
};



#endif