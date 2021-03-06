/** 
 * @file MeasureOfStraightLines.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/03/04
 * 
 * Header file for module MeasureOfStraightLines.cpp
 *
 * This file is part of the ImaGene library.
 */

#if defined(MeasureOfStraightLines_RECURSES)
#error Recursive header files inclusion detected in MeasureOfStraightLines.h
#else // defined(MeasureOfStraightLines_RECURSES)
/** Prevents recursive inclusion of headers. */
#define MeasureOfStraightLines_RECURSES

#if !defined MeasureOfStraightLines_h
/** Prevents repeated inclusion of headers. */
#define MeasureOfStraightLines_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
//////////////////////////////////////////////////////////////////////////////

namespace ImaGene 
{
  
  /////////////////////////////////////////////////////////////////////////////
  // class MeasureOfStraightLines
  /** 
   * Description of class 'MeasureOfStraightLines' <p>
   * Aim: 
   *
   * The aim of this class is to compute the measure in the Lebesgues
   * sense of the set of straight lines associated to domains defined
   * as polygons in the (a,b)-parameter space. This parameter space
   * maps the line $ax-y+b=0$ to the point $(a,b)$.
   *
   *
   * \verbatim
   * @inproceedings{COEURJOLLY:2009:HAL-00432711:1,
   *   title = { {M}easure of {S}traight {L}ines and its {A}pplications in {D}igital {G}eometry},
   *   author = {{C}oeurjolly, {D}avid and {S}ivignon, {I}sabelle},
   *   abstract = {{I}n digital geometry, objects such as digital straight lines can be considered as equivalent classes of {E}uclidean straight lines with re- spect to a digitization process. {T}his paper investigates the analysis of the set of straight lines whose digitization is a given digital straight seg- ment with the help of tools from integral geometry. {A}fter a definition of a measure on such sets, we illustrate several applications of it in digital geometry.},
   *   language = {{A}nglais},
   *   affiliation = {{L}aboratoire d'{I}nfo{R}matique en {I}mages et {S}yst{\`e}mes d'{I}nformation - {LIRIS} - {CNRS} : {UMR}5205 - {U}niversit{\'e} {C}laude {B}ernard - {L}yon {I} - {U}niversit{\'e} {L}umi{\`e}re - {L}yon {II} - {I}nstitut {N}ational des {S}ciences {A}ppliqu{\'e}es de {L}yon - {E}cole {C}entrale de {L}yon },
   *   booktitle = {13th {I}nternational {W}orkshop on {C}ombinatorial {I}mage {A}nalysis 13th {I}nternational {W}orkshop on {C}ombinatorial {I}mage {A}nalysis },
   *   publisher = {{R}esearch {P}ublishing {S}ervices },
   *   pages = {1-12 },
   *   address = {{C}ancun {M}exique },
   *   audience = {internationale },
   *   year = {2009},
   *   URL = {http://hal.archives-ouvertes.fr/hal-00432711/PDF/mesure.pdf},
   * }
   * \endverbatim
   *
   * \see test_measure.cpp
   *
   */
  class MeasureOfStraightLines
  {
    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Constructor. 
     */
    MeasureOfStraightLines();



    /**
     * Destructor. 
     */
    ~MeasureOfStraightLines();

    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay( std::ostream & out ) const;

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;


    /**
     * Compute the measure of the polygon {(a_i,b_i)} in the (a,b)-parameter space
     * 
     * REQUIREMENTS: 
     *   - The polygon is given counter-clockwise 
     *   - a_i > 0
     * 
     * @param a the a-value of polygon vertices
     * @param b the b-value of polygon vertices
     * @return the measure value (positive value)
     */
    double computeMeasure(const std::vector<double> &a,const std::vector<double> &b);

    
    /**
     * Compute the abscissa of the centroid of the polygon {(a_i,b_i)}
     * in the (a,b)-parameter space with respect to the measure of lines.
     * 
     * REQUIREMENTS: 
     *   - The polygon is given counter-clockwise 
     *   - a_i > 0
     * 
     * @param a the a-value of polygon vertices
     * @param b the b-value of polygon vertices
     * @return the measure value (positive value)
     */
    double computeCentroidA(const std::vector<double> &a,const std::vector<double> &b);

    
    /**
     * Compute the ordinate of the centroid of the polygon {(a_i,b_i)}
     * in the (a,b)-parameter space with respect to the measure of
     * lines. Note that there is a numerical approximation is
     * performed.
     * 
     * REQUIREMENTS: 
     *   - The polygon is given counter-clockwise 
     *   - a_i > 0
     * 
     * @param a the a-value of polygon vertices
     * @param b the b-value of polygon vertices
     * @return the measure value (positive value)
     */
    double computeCentroidB(const std::vector<double> &a,const std::vector<double> &b);


    /**
     * Set the internal Epsilon threshold for the numerical
     * approximation.
     *
     * @param aValue the new epsilon value
     */
    void setEpsilon(const double aValue);
    

    // ------------------------- Protected Datas ------------------------------
  private:
    // ------------------------- Private Datas --------------------------------
  private:
    double myEpsilon;

    // ------------------------- Hidden services ------------------------------
  protected:

  private:

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    MeasureOfStraightLines( const MeasureOfStraightLines & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    MeasureOfStraightLines & operator=( const MeasureOfStraightLines & other );
    
  
    // ------------------------- Internals ------------------------------------
  private:

    /**
     * Compute the measure associated to an edge (a0,b0)-(a1,b1)
     * It returns the measure of the triangle defined by the origin and the edge.
     *
     * @param a0
     * @param b0
     * @param a1
     * @param b1
     * @return the measure
     */
    double computeMeasureEdge ( double a0,double b0, double a1, double b1 );

    /**
     * Compute the abscissa of the centroid associated to an edge (a0,b0)-(a1,b1)
     * It returns the measure of the triangle defined by the origin and the edge.
     *
     * @param a0
     * @param b0
     * @param a1
     * @param b1
     * @return the measure
     */
    double computeCentroidEdge_a ( double a0,double b0, double a1, double b1 );

    /**
     * Compute the ordinate of the centroid associated to an edge (a0,b0)-(a1,b1)
     * It returns the measure of the triangle defined by the origin and the edge.
     *
     * @param a0
     * @param b0
     * @param a1
     * @param b1
     * @return the measure
     */  
    double computeCentroidEdge_b ( double a0,double b0, double a1, double b1 );
    
    /**
     * Approximate  the centroid on 'b' on the triangle (0,0)-(a0,b0)-(a1,b1) 
     * (internal function)
     **/
    double __computeCentroidTriApprox_b ( double a0, double b0,double a1,double b1 );
    
    /**
    * Approximate  the centroid on 'b' on the trapezioid  (a0,0)-(a0,b0)-(a1,b1)-(a1,0)
    * (internal function)
    **/
    double  __computeCentroidEdgeApprox_b ( double a0, double b0,double a1,double b1 );


    /**
    * Compute the centroid on 'b' on the rectangular domain with vertices (x1,,y1) - (x2,y2)
    * PRECONDITION: y1<y2
    *
    **/
    double __computeCentroidSquare_b ( double x1, double y1, double x2,double y2 );


    /**
     * @return the sign of a number (1 or -1)
     **/
    int sign ( double a );
     


  }; // end of class MeasureOfStraightLines


  /**
   * Overloads 'operator<<' for displaying objects of class 'MeasureOfStraightLines'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'MeasureOfStraightLines' to write.
   * @return the output stream after the writing.
   */
  std::ostream&
  operator<<( std::ostream & out, const MeasureOfStraightLines & object );

  
} // namespace ImaGene




//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined MeasureOfStraightLines_h

#undef MeasureOfStraightLines_RECURSES
#endif // else defined(MeasureOfStraightLines_RECURSES)
