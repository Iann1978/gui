//-------------------- -
//	作者：Ryannon
//	来源：CSDN
//	原文：https ://blog.csdn.net/ven_tink/article/details/52068160 
//版权声明：本文为博主原创文章，转载请附上博文链接！

#include "../../ext/triangle/triangle.h"
int main(void)
{
	struct triangulateio in, out;
	in.numberofpoints = 25;
	in.numberofpointattributes = 1;
	in.pointlist = (REAL *)malloc(in.numberofpoints * 2 * sizeof(REAL));
	for (size_t i = 0; i < in.numberofpoints; i++)
	{
		in.pointlist[2 * i] = pvertices_list_->at(i)->position().x();
		in.pointlist[2 * i + 1] = pvertices_list_->at(i)->position().y();
	}
	in.pointmarkerlist = (int *)malloc(in.numberofpoints * sizeof(int));
	for (size_t i = 0; i < in.numberofpoints; i++)
	{
		in.pointmarkerlist[i] = 1;
	}
	in.pointattributelist = (REAL *)malloc(in.numberofpoints *
		in.numberofpointattributes *
		sizeof(REAL));
	for (size_t i = 0; i < in.numberofpoints; i++)
	{
		in.pointattributelist[i] = 10;
	}

	in.numberofsegments = in.numberofpoints;
	in.segmentlist = (int*)malloc(in.numberofpoints * 2 * sizeof(int));

	for (size_t i = 0; i < in.numberofsegments; i++)
	{
		if (i == in.numberofsegments - 1)
		{
			in.segmentlist[2 * i] = i;
			in.segmentlist[2 * i + 1] = 0;
		}
		else
		{
			in.segmentlist[2 * i] = i;
			in.segmentlist[2 * i + 1] = i + 1;
		}
	}
	in.segmentmarkerlist = (int*)malloc(in.numberofsegments * sizeof(int));
	for (size_t i = 0; i < in.numberofsegments; i++)
	{
		in.segmentmarkerlist[i] = 1;
	}

	in.numberofholes = 0;
	in.numberofregions = 0;

	out.pointlist = (REAL *)NULL;            /* Not needed if -N switch used. */
											 /* Not needed if -N switch used or number of point attributes is zero: */
	out.pointattributelist = (REAL *)NULL;
	out.pointmarkerlist = (int *)NULL; /* Not needed if -N or -B switch used. */
	out.trianglelist = (int *)NULL;          /* Not needed if -E switch used. */
											 /* Not needed if -E switch used or number of triangle attributes is zero: */
	out.triangleattributelist = (REAL *)NULL;
	out.neighborlist = (int *)NULL;         /* Needed only if -n switch used. */
											/* Needed only if segments are output (-p or -c) and -P not used: */
	out.segmentlist = (int *)NULL;
	/* Needed only if segments are output (-p or -c) and -P and -B not used: */
	out.segmentmarkerlist = (int *)NULL;
	out.edgelist = (int *)NULL;             /* Needed only if -e switch used. */
	out.edgemarkerlist = (int *)NULL;   /* Needed if -e used and -B not used. */

	triangulate("pzAen", &in, &out, (struct triangulateio *) NULL);

	return 0;
}