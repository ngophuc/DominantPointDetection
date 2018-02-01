#include "DominantPointDetection.h"

void drawCanvas(Board2D &aBoard, unsigned int w, unsigned int h){
    aBoard.setLineWidth(0);
    aBoard.drawLine(0, 0, w, 0);
    aBoard.drawLine(w, 0, w, h);
    aBoard.drawLine(w, h, 0, h);
    aBoard.drawLine(0, h, 0, 0);
}

/*************************************/
/*** Burred segments decomposition ***/
/*************************************/
vector<AlphaThickSegmentComputer2DD> blurredSegmentDecomposition(const vector<RealPoint>& aContour, double thickness, const char* filename)
{
    vector<AlphaThickSegmentComputer2DD> fuzzySegmentSet;
    //run over the points on the contours
    for(vector<RealPoint>::const_iterator it=aContour.begin();it!=aContour.end();it++)
    {
        AlphaThickSegmentComputer2DD aSegment(thickness);
        aSegment.init(it);
        /* travel over the contour points and add to the seg */
        while (aSegment.end()!=aContour.end() && aSegment.extendFront()){;}
        if(it==aContour.begin())
            fuzzySegmentSet.push_back(aSegment);
        else if(findElement(aContour,getEndPoint(aSegment))>findElement(aContour,getEndPoint(fuzzySegmentSet.back())))
            fuzzySegmentSet.push_back(aSegment);
        if(getEndPoint(aSegment)==aContour.back() || it==aContour.end())
            break;
    }

    if(filename!=NULL)
    {
        std::string n (filename);
        std::string outputExt = n.substr(n.find_last_of(".")+1);
        Board2D aBoard;
        /* display the boundary */
        aBoard << SetMode("PointVector", "Both");
        for(vector<RealPoint>::const_iterator it=aContour.begin(); it!=aContour.end(); it++)
            aBoard << *it;
        /* display the boundary */
        /* Display boundingbox */
        for(vector<AlphaThickSegmentComputer2DD>::const_iterator it=fuzzySegmentSet.begin();it!=fuzzySegmentSet.end();it++)
            aBoard << SetMode((*it).className(), "BoundingBox")
                   <<(*it);
        /* Display boundingbox */
        if(outputExt=="svg"){
            aBoard.saveSVG(filename);
        }
        else if (outputExt == "eps"){
            aBoard.saveEPS(filename);
        }
    }
    return fuzzySegmentSet;
}
/*************************************/
/*** Burred segments decomposition ***/
/*************************************/

/*********************************************************/
/********* Adaptive Tangent Cover computation ************/
/*********************************************************/
vector<AlphaThickSegmentComputer2DD> adaptiveTangentCoverDecomposition(const vector<RealPoint>& aContour, const vector<double>& vecMT)
{
    //1. Find vector of thickness element
    vector<double> meaningThicknessElement;
    meaningThicknessElement.push_back(vecMT.front());
    for(vector<double>::const_iterator it = vecMT.begin()+1; it != vecMT.end(); it++)
    {
        double m = (*it);
        if (std::find(meaningThicknessElement.begin(), meaningThicknessElement.end(),m)==meaningThicknessElement.end())
            meaningThicknessElement.push_back(m);
    }
    std::sort(meaningThicknessElement.begin(),meaningThicknessElement.end(),sort_increase);

    //2. Compute different thickness tangent covers (blurred segments)
    vector<vector<AlphaThickSegmentComputer2DD> > meaningThicknessTangentCover(meaningThicknessElement.size());
    int index = 0;
    for(vector<double>::const_iterator it = meaningThicknessElement.begin(); it != meaningThicknessElement.end(); it++)
    {
        double thickness = (*it)*sqrt(2);
        cout<<"thickness="<<thickness<<endl;
        vector<AlphaThickSegmentComputer2DD> fuzzySegmentSet = blurredSegmentDecomposition(aContour,thickness,NULL);
        cout<<"===> Num of seg decomposed is "<<fuzzySegmentSet.size()<<endl;
        for (vector<AlphaThickSegmentComputer2DD>::const_iterator it_bis = fuzzySegmentSet.begin();it_bis != fuzzySegmentSet.end();it_bis++)
            meaningThicknessTangentCover[index].push_back(*it_bis);
        index++;
    }

    //3. Update thickness of points with tangent covers
    vector<double> vecMTmodified;
    for(vector<double>::const_iterator it = vecMT.begin(); it != vecMT.end(); it++)
        vecMTmodified.push_back(*it);
    for(int it=meaningThicknessTangentCover.size()-1; it>=0; it--)
    {
        vector<AlphaThickSegmentComputer2DD> fuzzySegmentSet = meaningThicknessTangentCover.at(it);//*it;
        double thickness = meaningThicknessElement.at(it);
        for (vector<AlphaThickSegmentComputer2DD>::const_iterator it_bis = fuzzySegmentSet.begin();it_bis != fuzzySegmentSet.end();it_bis++)
        {
            int idStart = findElement(aContour,getStartPoint(*it_bis));
            int idEnd = findElement(aContour,getEndPoint(*it_bis),idStart);
            if(idStart != -1 && idEnd != -1)
            {
                double maxThickness = -1;
                for(int i=idStart; i<=idEnd; i++)
                {
                    double thicknessPoint = vecMT.at(i);
                    if(thicknessPoint > maxThickness)
                        maxThickness = thicknessPoint;
                }
                for(int i=idStart; i<=idEnd; i++)
                {
                    if(maxThickness==thickness)//vecMTmodified.at(i) < maxThickness &&
                        vecMTmodified.at(i) = maxThickness;
                }
            }
            else
                cout<<"negatif"<<endl;
        }
    }

    //4. Travel over the tangent covers and select the segments w.r.t the associated thickness of points
    vector<vector<AlphaThickSegmentComputer2DD> > adaptiveMeaningThicknessTangentCover;
    int idCover = 0;
    for(vector<vector<AlphaThickSegmentComputer2DD> >::const_iterator it = meaningThicknessTangentCover.begin(); it != meaningThicknessTangentCover.end(); it++)
    {
        adaptiveMeaningThicknessTangentCover.push_back(vector<AlphaThickSegmentComputer2DD>());
        vector<AlphaThickSegmentComputer2DD> fuzzySegmentSet = *it;
        vector<AlphaThickSegmentComputer2DD> AdaptiveFuzzySegmentSet;
        int idSeg=0;
        double thickness = meaningThicknessElement.at(idCover);
        for (vector<AlphaThickSegmentComputer2DD>::const_iterator it_bis = fuzzySegmentSet.begin();it_bis != fuzzySegmentSet.end();it_bis++)
        {
            int idStart = findElement(aContour,getStartPoint(*it_bis));
            int idEnd = findElement(aContour,getEndPoint(*it_bis));
            if(idStart != -1 && idEnd != -1)
            {
                bool isGoodMTmodif = false, isGoodMT = false;//true
                for(int i=idStart; i<=idEnd; i++)
                {
                    double thicknessMT = vecMT.at(i); //all elt have same meaningful thickness value (dont contain other meaningful thickness)
                    if(thicknessMT == thickness)
                        isGoodMT = true;
                    double thicknessMTmodif = vecMTmodified.at(i);
                    if(thicknessMTmodif == thickness) //there exist at least one elt in modif having meaningful thickness value
                        isGoodMTmodif = true;
                }
                if(isGoodMTmodif && isGoodMT)
                    AdaptiveFuzzySegmentSet.push_back(*it_bis);
            }
            idSeg++;
        }
        for (vector<AlphaThickSegmentComputer2DD>::const_iterator it_bis = AdaptiveFuzzySegmentSet.begin();it_bis != AdaptiveFuzzySegmentSet.end();it_bis++)
            adaptiveMeaningThicknessTangentCover[idCover].push_back(*it_bis);
        idCover++;
    }
    for(vector<vector<AlphaThickSegmentComputer2DD> >::reverse_iterator it1 = adaptiveMeaningThicknessTangentCover.rbegin(); it1 != adaptiveMeaningThicknessTangentCover.rend(); ++it1)
    {
        vector<AlphaThickSegmentComputer2DD>& segmentSet1 = *it1;
        for(vector<vector<AlphaThickSegmentComputer2DD> >::reverse_iterator it2 = it1+1; it2 != adaptiveMeaningThicknessTangentCover.rend(); ++it2)
        {
            vector<AlphaThickSegmentComputer2DD>& segmentSet2 = *it2;
            for (vector<AlphaThickSegmentComputer2DD>::iterator itSeg1 = segmentSet1.begin();itSeg1 != segmentSet1.end();itSeg1++)
            {
                int idCurrentStart = findElement(aContour,getStartPoint(*itSeg1));
                int idCurrentEnd = findElement(aContour,getEndPoint(*itSeg1),idCurrentStart);
                for (vector<AlphaThickSegmentComputer2DD>::iterator itSeg2 = segmentSet2.begin();itSeg2 != segmentSet2.end();itSeg2++)
                {
                    int idStart = findElement(aContour,getStartPoint(*itSeg2));
                    int idEnd = findElement(aContour,getEndPoint(*itSeg2),idStart);
                    if(idCurrentStart<=idStart && idCurrentEnd>=idEnd)
                    {
                        segmentSet2.erase(itSeg2);
                        itSeg2--;
                    }
                }
            }
        }
    }

    //5. Reorder the multi-thickness tangent cover
    vector<AlphaThickSegmentComputer2DD> adaptiveTangentCover;
    int seg=0,nbSeg=0;
    vector<int> idThicknessCover; //stock idSeg of the last seg at idThicknessCover
    for(int it=0; it<meaningThicknessElement.size();it++)
        idThicknessCover.push_back(0);
    for(int it = 0; it < adaptiveMeaningThicknessTangentCover.size(); it++)
        nbSeg += (adaptiveMeaningThicknessTangentCover.at(it)).size();

    while (seg<nbSeg)
    {
        int idMinStart = aContour.size(), idMinEnd = aContour.size();
        int idMin=-1, idSeg=-1;
        //scan adaptiveMeaningThicknessTangentCover
        for(int it = 0; it < adaptiveMeaningThicknessTangentCover.size(); it++)//thickness level = it
        {
            //current seg of thickness level idThicknessCover.at(i)
            int idCurrentSeg = idThicknessCover.at(it);
            if(idCurrentSeg<(adaptiveMeaningThicknessTangentCover.at(it)).size())
            {
                //get idStart and idEnd of seg
                int idCurrentStart = findElement(aContour,getStartPoint((adaptiveMeaningThicknessTangentCover.at(it)).at(idCurrentSeg)));
                int idCurrentEnd = findElement(aContour,getEndPoint((adaptiveMeaningThicknessTangentCover.at(it)).at(idCurrentSeg)),idCurrentStart);
                if(idThicknessCover.at(it)<(adaptiveMeaningThicknessTangentCover.at(it)).size())
                {
                    //find min idCurrentStart
                    if(idMinStart==idCurrentStart && idMinEnd<idCurrentEnd)
                    {
                        if(idThicknessCover.at(it)<(adaptiveMeaningThicknessTangentCover.at(it)).size()-1)
                        {
                            idThicknessCover.at(idMin) = idThicknessCover.at(idMin) + 1;
                            seg++;
                        }
                        idSeg = idCurrentSeg;
                        idMin = it;
                        idMinStart = idCurrentStart;
                        idMinEnd = idCurrentEnd;
                    }
                    else if(idMinStart>idCurrentStart && idMinEnd>=idCurrentEnd)
                    {
                        idSeg = idCurrentSeg;
                        idMin = it;
                        idMinStart = idCurrentStart;
                        idMinEnd = idCurrentEnd;
                    }
                }
            }
        }
        adaptiveTangentCover.push_back((adaptiveMeaningThicknessTangentCover.at(idMin)).at(idSeg));
        idThicknessCover.at(idMin) = idThicknessCover.at(idMin) + 1;
        seg++;
    }

    return adaptiveTangentCover;
}

vector<vector<AlphaThickSegmentComputer2DD> > adaptiveTangentCoverDecomposition(const vector<vector<RealPoint> >& aContour, const vector<vector<double> >& vecMT, std::string filename, unsigned int w, unsigned int h)
{
    vector<vector<AlphaThickSegmentComputer2DD> > vecATC;
    for(size_t it_contour=0; it_contour<aContour.size(); it_contour++)
        vecATC.push_back(adaptiveTangentCoverDecomposition(aContour.at(it_contour),vecMT.at(it_contour)));

    Board2D aBoard;
    if(w!=0 && h!=0)
        drawCanvas(aBoard, w, h);
    GradientColorMap<int> cmap_grad( 0, aContour.size()+1 );
    cmap_grad.addColor( Color( 50, 50, 255 ) );
    cmap_grad.addColor( Color( 255, 0, 0 ) );
    cmap_grad.addColor( Color( 255, 255, 10 ) );
    cmap_grad.addColor( Color( 25, 255, 255 ) );
    cmap_grad.addColor( Color( 255, 25, 255 ) );
    cmap_grad.addColor( Color( 25, 25, 25 ) );
    for(size_t it_contour=0; it_contour<aContour.size(); it_contour++)
        for (vector<AlphaThickSegmentComputer2DD>::const_iterator it=vecATC.at(it_contour).begin(); it != vecATC.at(it_contour).end(); ++it)
            aBoard << SetMode((*it).className(), "BoundingBox")
                   << CustomStyle("AlphaThickSegment/BoundingBox",  new CustomPenColor(cmap_grad(it_contour)))
                   << *it;
    std::string outputExt = filename.substr(filename.find_last_of(".")+1);
    if(outputExt=="svg")
        aBoard.saveSVG(filename.c_str());
    else if (outputExt == "eps")
        aBoard.saveEPS(filename.c_str());

    return vecATC;
}
/*********************************************************/
/********* Adaptive Tangent Cover computation ************/
/*********************************************************/

/************************************/
/**** Dominant points detections ****/
/************************************/
vector<RealPoint> dominantPointDetection(const vector<AlphaThickSegmentComputer2DD>& vecTangentCover, const vector<RealPoint>& aContour)
{
    int p=1, q=0, Eq=0, Bp=0, m=vecTangentCover.size();
    vector<RealPoint> pile;
    while (p<m && q<m && Bp>=0 && Eq>=0)
    {
        Bp = findStartElement(aContour,vecTangentCover[p]);
        Eq = findEndElement(aContour,vecTangentCover[q]);
        while(Eq>=Bp && p<m && q<m && Bp>=0 && Eq>=0 )
        {
            Bp = findStartElement(aContour,vecTangentCover[p]);
            Eq = findEndElement(aContour,vecTangentCover[q]);
            p++;
        }
        if(Eq<Bp)
        {
            p--;//when out of loop => Eq<Bp
            pile.push_back(RealPoint(q,p-1));
            q=p-1;
        }
        else
        {
            if(p>=m || q>=m)
                pile.push_back(RealPoint(q,p-1));
            else
                q = p;
        }
    }
    /* pile construction */

    /* calcul point dominant */
    vector<RealPoint> DP;
    for(vector<RealPoint>::const_iterator it = pile.begin(); it != pile.end(); it++)
    {
        q = (*it)[0];
        p = (*it)[1];
        //find point with max (local) curvature
        int indexB = findStartElement(aContour,vecTangentCover[p]);
        int indexE = findEndElement(aContour,vecTangentCover[q]);
        int indexC = indexB;
        int indexBi = findStartElement(aContour,vecTangentCover[q]);
        int indexEi = findEndElement(aContour,vecTangentCover[p]);

        for(int i = indexB+1; i<=indexE; i++)
        {
            int modIndex = i;
            if(fabs(acuteAngle(aContour.at(indexBi),aContour.at(modIndex),aContour.at(indexEi))) <=
                    fabs(acuteAngle(aContour.at(indexBi),aContour.at(indexC),aContour.at(indexEi))))
                indexC = modIndex;
        }

        if(DP.empty() || aContour[indexC] != DP.back())
            DP.push_back(aContour[indexC]);
    }
    DP.insert(DP.begin(),aContour.front());
    DP.insert(DP.end(),aContour.back());
    /* calcul point dominant */

    return DP;
}

vector<vector<RealPoint> > dominantPointDetection(const vector<vector<AlphaThickSegmentComputer2DD> >& vecTangentCover, const vector<vector<RealPoint> >& aContour, string filename, unsigned int w, unsigned int h)
{
    vector<vector<RealPoint> > vecDP;
    for(size_t it_contour=0; it_contour<aContour.size(); it_contour++)
        //cout<<"contour "<<it_contour<<": size="<<aContour.at(it_contour).size()<<endl;
        vecDP.push_back(dominantPointDetection(vecTangentCover.at(it_contour),aContour.at(it_contour)));

    Board2D aBoard;
    if(w!=0 && h!=0)
        drawCanvas(aBoard, w, h);
    aBoard << SetMode("PointVector", "Grid");
    GradientColorMap<int> cmap_grad( 0, aContour.size()+1 );
    cmap_grad.addColor( Color( 50, 50, 255 ) );
    cmap_grad.addColor( Color( 255, 0, 0 ) );
    cmap_grad.addColor( Color( 255, 255, 10 ) );
    cmap_grad.addColor( Color( 25, 255, 255 ) );
    cmap_grad.addColor( Color( 255, 25, 255 ) );
    cmap_grad.addColor( Color( 25, 25, 25 ) );
    for(size_t it_contour=0; it_contour<aContour.size(); it_contour++)
    {
        /* Display the boundary */
        for (vector<RealPoint>::const_iterator it = aContour.at(it_contour).begin(); it != aContour.at(it_contour).end(); it++)
            aBoard << *it;
        /* Display the boundary */
        /* Display the segments by DP */
        aBoard.setPenColor(cmap_grad(it_contour));
        aBoard.setLineWidth(100.0);
        for(vector<RealPoint>::const_iterator it = vecDP.at(it_contour).begin(); it+1 != vecDP.at(it_contour).end(); it++)
            aBoard.drawLine((*it)[0],(*it)[1],(*(it+1))[0],(*(it+1))[1]);
        /* Display the segments by DP */
    }

    std::string outputExt = filename.substr(filename.find_last_of(".")+1);
    if(outputExt=="svg")
        aBoard.saveSVG(filename.c_str());
    else if (outputExt == "eps")
        aBoard.saveEPS(filename.c_str());

    return vecDP;
}
/************************************/
/**** Dominant points detections ****/
/************************************/

/***********************************/
/**** Dominant points selection ****/
/***********************************/
vector<RealPoint> dominantPointSimplification(const vector<RealPoint>& DP, const vector<int>& indexDP, const vector<RealPoint>& aContour)
{
    vector<RealPoint> selectedDP;
    for(vector<RealPoint>::const_iterator it = DP.begin(); it != DP.end(); it++)
        selectedDP.push_back(*it);
    vector<int> indexSelectedDP;
    for(vector<int>::const_iterator it = indexDP.begin(); it != indexDP.end(); it++)
        indexSelectedDP.push_back(*it);
    vector<double> iseDP;
    double ise = error_ISE(aContour,selectedDP,indexSelectedDP,false);
    double cr = error_CR(aContour,selectedDP);
    double error_prev, error;
    error_prev = error = (cr*cr)/ise;
    int lastIndex=-1,lastIndexSelectedDP=-1;
    RealPoint lastSelectedDP;

    while(error_prev <= error){
        error_prev = error;
        iseDP.push_back(aContour.size()*aContour.size());//Keep the fist point as DP
        //cout<<"iseDP first="<<iseDP.back()<<endl;
        for(int it = 1; it+1 < selectedDP.size(); it++)
        {
            double ise = 0.0, d = 0.0, angle = 0.0;
            int indexStart = indexSelectedDP.at(it-1);
            int indexEnd = indexSelectedDP.at(it+1);
            if(indexStart < 0 || indexEnd < 0)
                cout<<"Pb in error_ISE index of DP"<<endl;
            for(int index = indexStart+1; index < indexEnd; index++)
            {
                d = distancePointSegment(aContour.at(index),aContour.at(indexStart), aContour.at(indexEnd));
                ise += d*d;
            }
            angle = acuteAngle(aContour.at(indexStart),
                               aContour.at(indexSelectedDP.at(it)),
                               aContour.at(indexEnd));
            iseDP.push_back(ise/angle);
            //cout<<"it "<<it<<" : iseDP "<<iseDP.back()<<endl;
        }
        iseDP.push_back(aContour.size()*aContour.size());//Keep the fist point as DP
        //cout<<"iseDP last="<<iseDP.back()<<endl;

        vector<int> indexOrderedDP = absSortIndex(iseDP,true);
        /* erease the first elt */
        lastIndex = indexOrderedDP.front();
        lastSelectedDP = selectedDP.at(lastIndex);
        lastIndexSelectedDP = indexSelectedDP.at(lastIndex);
        //cout<<"=> min ise at "<<indexOrderedDP.front()<<endl;
        selectedDP.erase(selectedDP.begin()+indexOrderedDP.front());
        indexSelectedDP.erase(indexSelectedDP.begin()+indexOrderedDP.front());
        iseDP.clear();
        /* erease the first elt */

        /* update errors */
        ise = error_ISE(aContour,selectedDP,indexSelectedDP,false);
        cr = error_CR(aContour,selectedDP);
        error = (cr*cr)/ise;
        /* update errors */
    }
    /* Push back the last element */
    if(lastIndex !=-1)
    {
        selectedDP.insert(selectedDP.begin()+lastIndex,lastSelectedDP);
        indexSelectedDP.insert(indexSelectedDP.begin()+lastIndex,lastIndexSelectedDP);
    }
    /* Push back the last element */

    return selectedDP;
}

vector<vector<RealPoint> > dominantPointSimplification(const vector<vector<RealPoint> > &DP, const vector<vector<int> >& indexDP, const vector<vector<RealPoint> > &aContour, string filename, unsigned int w, unsigned int h)
{
    vector<vector<RealPoint> > selectedDP;
    for(size_t it_contour=0; it_contour<aContour.size(); it_contour++)
        selectedDP.push_back(dominantPointSimplification(DP.at(it_contour),indexDP.at(it_contour),aContour.at(it_contour)));

    Board2D aBoard;
    if(w!=0 && h!=0)
        drawCanvas(aBoard, w, h);
    /* Display the boundary */
    aBoard << SetMode("PointVector", "Both");
    for(size_t it_contour=0; it_contour<aContour.size(); it_contour++)
    {
        for (vector<RealPoint>::const_iterator it = aContour.at(it_contour).begin(); it != aContour.at(it_contour).end(); it++)
            aBoard << *it;
        /* Display the boundary */
        aBoard.setLineWidth(100.0);
        /* Display the segments by old DP *
        aBoard.setPenColor(Color(192, 0, 0));
        for(vector<RealPoint>::const_iterator it = DP.at(it_contour).begin(); it+1 != DP.at(it_contour).end(); it++)
            aBoard.drawLine((*it)[0],(*it)[1],(*(it+1))[0],(*(it+1))[1]);
        /* Display the segments by old DP */
        /* Display the segments by new DP */
        aBoard.setPenColor(Color(0, 192, 0));
        for(vector<RealPoint>::const_iterator it = selectedDP.at(it_contour).begin(); it+1 != selectedDP.at(it_contour).end(); it++)
            aBoard.drawLine((*it)[0],(*it)[1],(*(it+1))[0],(*(it+1))[1]);
        /* Display the segments by new DP */
    }
    std::string outputExt = filename.substr(filename.find_last_of(".")+1);
    if(outputExt=="svg")
        aBoard.saveSVG(filename.c_str());
    else if (outputExt == "eps")
        aBoard.saveEPS(filename.c_str());

    return selectedDP;
}
/************************************/
/**** Dominant points selection *****/
/************************************/
