// This file is part of FeynSimul.
//
// FeynSimul is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// FeynSimul is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with FeynSimul.  If not, see <http://www.gnu.org/licenses/>.

// -*- coding: utf-8 -*-
inline FLOAT_TYPE sqr(FLOAT_TYPE x)
{
    return x*x;
}                 
//The following functions take r in Angstrom and return energy in K
inline FLOAT_TYPE lm2m2sqrt(FLOAT_TYPE sr)
{
    //source: physics.nist.gov
    FLOAT_TYPE k=8.6173324e-5; //eV/K boltzmann constant, 

    // source: lm2m2-part of table V in JChemPhys_94_8047.pdf
    // A, beta, and alpha have a star in JChemPhys_94_8047.pdf
    // but not in SR. A. Aziz and H. H. Chen, J. Chern. Phys. 67,
    // 5719 (1977) were the expression for the base potential is.
    // c6, c8 and c10 were capital letters in one of the
    // sources but not in the other.
    FLOAT_TYPE A=1.89635353e5;
    FLOAT_TYPE alpha=10.70203539;
    FLOAT_TYPE c6=1.34687065;
    FLOAT_TYPE c8=0.41308398;
    FLOAT_TYPE c10=0.17060159;
    FLOAT_TYPE D=1.4088;
    FLOAT_TYPE beta=-1.90740649;
    FLOAT_TYPE epsilon_over_k=10.97;//K
    FLOAT_TYPE rm=2.9695; //Angstrom;

    FLOAT_TYPE Aa=0.0026000000;
    FLOAT_TYPE xa1 = 1.0035359490;
    FLOAT_TYPE xa2 = 1.4547903690;

    FLOAT_TYPE x=sqrt(sr)/rm;
    FLOAT_TYPE x2=x*x;
    FLOAT_TYPE x6=x2*x2*x2;
    FLOAT_TYPE x8=x6*x2;
    FLOAT_TYPE x10=x8*x2;

    //Vb_star=base potential, reduced form
    //source: SR. A. Aziz and H. H. Chen, J. Chern. Phys. 67, 		// 5719 (1977)
    FLOAT_TYPE F_times_rational;
    if(x<D)
    {
        if(x>0.0005/rm)
        {
            F_times_rational=exp(-(D/x-1.0)*(D/x-1.0))*(c6/x6+c8/x8+c10/x10);
        } else {
            F_times_rational=0.0;
        }
    } else {
        F_times_rational=c6/x6+c8/x8+c10/x10;
    }
    FLOAT_TYPE Vb_star=A*exp(-alpha*x+beta*x2)-F_times_rational;

    //Va_star=addon potential, reduced form
    //source: JChemPhys_94_8047.pdf
    FLOAT_TYPE Va_star;
    if(x<xa1 || x>xa2)
    {
        Va_star=0.0;
    } else {
        FLOAT_TYPE B=2.0*M_PI/(xa2-xa1);
        Va_star=Aa*(sin(B*(x-xa1)-M_PI_2)+1.0);
    }
    
    return epsilon_over_k*(Vb_star+Va_star);
}

inline FLOAT_TYPE dlm2m2sqrtdr(FLOAT_TYPE sr)
{
    //source: physics.nist.gov
    FLOAT_TYPE k=8.6173324e-5; //eV/K boltzmann constant, 

    // source: lm2m2-part of table V in JChemPhys_94_8047.pdf
    // A, beta, and alpha have a star in JChemPhys_94_8047.pdf
    // but not in SR. A. Aziz and H. H. Chen, J. Chern. Phys. 67,
    // 5719 (1977) were the expression for the base potential is.
    // c6, c8 and c10 alsa where capital letters in one of the
    // sources but not in the other.
    FLOAT_TYPE A=1.89635353e5;
    FLOAT_TYPE alpha=10.70203539;
    FLOAT_TYPE c6=1.34687065;
    FLOAT_TYPE c8=0.41308398;
    FLOAT_TYPE c10=0.17060159;
    FLOAT_TYPE D=1.4088;
    FLOAT_TYPE beta=-1.90740649;
    FLOAT_TYPE epsilon_over_k=10.97;//K
    FLOAT_TYPE rm=2.9695; //Angstrom;

    FLOAT_TYPE Aa=0.0026000000;
    FLOAT_TYPE xa1 = 1.0035359490;
    FLOAT_TYPE xa2 = 1.4547903690;
    FLOAT_TYPE r=sqrt(sr);
    FLOAT_TYPE x=r/rm;
    FLOAT_TYPE x2=x*x;
    FLOAT_TYPE x6=x2*x2*x2;
    FLOAT_TYPE x7=x6*x;
    FLOAT_TYPE x8=x6*x2;
    FLOAT_TYPE x9=x8*x;
    FLOAT_TYPE x10=x8*x2;
    FLOAT_TYPE x11=x10*x;

    //Vb_star=base potential, reduced form
    //source: SR. A. Aziz and H. H. Chen, J. Chern. Phys. 67,
    // 5719 (1977)
    FLOAT_TYPE dF_times_rationaldx;
    if(x<D)
    {
        if(x>0.0005/rm)
        {
            dF_times_rationaldx=exp(-(D/x-1.0)*(D/x-1.0))*(-6.0*c6/x7-8.0*c8/x9-10.0*c10/x11)+
                exp(-(D/x-1.0)*(D/x-1.0))*(-2.0*(D/x-1.0)*(-D/x2))*(c6/x6+c8/x8+c10/x10);
        } else {
            dF_times_rationaldx=0.0;
        }
    } else {
        dF_times_rationaldx=-6.0*c6/x7-8.0*c8/x9-10.0*c10/x11;
    }
    FLOAT_TYPE dVb_stardx=A*exp(-alpha*x+beta*x2)*(-alpha+beta*2.0*x)-dF_times_rationaldx;

    //Va_star=addon potential, reduced form
    //source: JChemPhys_94_8047.pdf
    FLOAT_TYPE dVa_stardx;
    if(x<xa1 || x>xa2)
    {
        dVa_stardx=0.0;
    } else {
        FLOAT_TYPE B=2.0*M_PI/(xa2-xa1);
        dVa_stardx=Aa*(cos(B*(x-xa1)-M_PI_2)*B+1.0);
    }
    
    return epsilon_over_k*(dVb_stardx+dVa_stardx)/(rm*2.0*r);//..*2.0*r) because of sqrt
} 
