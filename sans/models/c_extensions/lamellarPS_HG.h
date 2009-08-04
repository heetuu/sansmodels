/*
	TODO: Add 2D model
*/

#if !defined(lamellarPS_HG_h)
#define lamellarPS_HG_h
/** Structure definition for concentrated lamellar form factor parameters
 * [PYTHONCLASS] = LamellarPSHGModel
 * [DISP_PARAMS] = deltaT,deltaH,spacing
   [DESCRIPTION] = <text>[Concentrated Lamellar (head+tail) Form Factor]: Calculates the
	   intensity from a lyotropic lamellar phase.
	   The intensity (form factor and structure factor)
		calculated is for lamellae of two-layer scattering
		length density that are randomly distributed in
		solution (a powder average). The scattering
		length density of the tail region, headgroup
		region, and solvent are taken to be different.
		The model can also be applied to large,
		multi-lamellar vesicles.
		No resolution smeared version is included
		in the structure factor of this model.
		*Parameters: spacing = repeat spacing,
		deltaT = tail length,
		deltaH = headgroup thickness,
		n_plates = # of Lamellar plates
		caille = Caille parameter (<0.8 or <1)
		background = incoherent bgd
		scale = scale factor ...
</text>
   [FIXED]= deltaT.width;deltaH.width;spacing.width
   [ORIENTATION_PARAMS]=

 **/
typedef struct {
    /// Scale factor
    //  [DEFAULT]=scale=1.0
    double scale;
    /// repeat spacing of the lamellar [A]
    //  [DEFAULT]=spacing=40 [A]
    double spacing;
	///  tail thickness [A]
    //  [DEFAULT]=deltaT=10 [A]
    double deltaT;
	///  head thickness [A]
    //  [DEFAULT]=deltaH=2.0 [A]
    double deltaH;
    /// scattering density length of tails [1/A�]
    //  [DEFAULT]=sld_tail=0.4e-6 [1/A�]
    double sld_tail;
	/// scattering density length of head [1/A�]
    //  [DEFAULT]=sld_head=2e-6 [1/A�]
    double sld_head;
	/// scattering density length of solvent [1/A�]
    //  [DEFAULT]=sld_solvent=6e-6 [1/A�]
    double sld_solvent;
	 /// Number of lamellar plates
    //  [DEFAULT]=n_plates=30
    double n_plates;
    /// caille parameters
    //  [DEFAULT]=caille=0.001
    double caille;
	/// Incoherent Background [1/cm]
	//  [DEFAULT]=background=0.001 [1/cm]
	double background;

} LamellarPSHGParameters;



/// 1D scattering function
double lamellarPS_HG_analytical_1D(LamellarPSHGParameters *pars, double q);

/// 2D scattering function
double lamellarPS_HG_analytical_2D(LamellarPSHGParameters *pars, double q, double phi);
double lamellarPS_HG_analytical_2DXY(LamellarPSHGParameters *pars, double qx, double qy);

#endif
