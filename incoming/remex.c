/*   FIR filter design program using the REMEZ EXCHANGE algorithm   */
/*                                                                  */
/*                      transcribed from                            */
/*      'THEORY AND APPLICATION OF DIGITAL SIGNAL PROCESSING'       */
/*                written by L.R.Rabiner & B.Gold                   */
/*                                                                  */


#include	<stdio.h>
#include	<math.h>

#define	PI		3.14159265358979
#define	NFMAX	512
#define	JMAX	(NFMAX/2+2)
#define	IMAX	16*JMAX
#define	NBMAX	10

int		jtype,nfilt,nfcns,ngrid,nbands,neg,nodd;

double	dev,
		ln10,hr,
		eff(),wate(),d(),gee(),
		sin(),cos(),acos(),log();

int		iext[JMAX+1];

double	ad[JMAX+1],alpha[JMAX+1],x[JMAX+1],y[JMAX+1],h[JMAX+1],
		des[IMAX+1],grid[IMAX+1],wt[IMAX+1],
		edge[2*NBMAX+1],fx[NBMAX+1],wtx[NBMAX+1],deviat[NBMAX+1],
		a[JMAX+1],p[JMAX+1],q[JMAX+1];

char	s[81],filename[81];

FILE	*fp_w;

main()
{
	fprintf(stderr,"\n***** FIR filter design *****");
	fprintf(stderr, "\n  number of bands = ?");
	scanf("%s", s);
	sscanf(s, "%d", &nbands);
	fprintf(stderr,"\b\r  number of bands = %d             ",nbands);

	for(;;) {
		fir_coef();
		fprintf(stderr, "\n again (y/n) ?");
		scanf("%s", s);
		if(toupper(s[0])!='Y')
			break;
	}
}


fir_coef()
{
	int		lgrid,jb,j,l,lband,nm1,nz;
	double	delf,fup,temp,change;

	ln10=log(10.0);
/* SKIP1 */
	dev=0.0;
	nfcns=0;
	ngrid=0;
	lgrid=16;
	jtype=1;

	fprintf(stderr,"\n  filter length = ?");
	scanf("%s", s);
	sscanf(s, "%d", &nfilt);
	fprintf(stderr,"\b\r  filter length = %d             ",nfilt);
	if((nfilt<3)||(NFMAX<nfilt)) {
		fprintf(stderr,"\n filter length must be  3 to %d",NFMAX);
		return;
	}
/* SKIP2 */
	if(nbands<=0)
		nbands=1;
	if(lgrid<=0)
		lgrid=16;
	jb=2*nbands;
	fprintf(stderr,"\n band edge frequency (0 - 0.5)");
	for(j=1;j<=nbands;j++) {
		fprintf(stderr, "\n  lower edge of band(%d) = ?",j);
		scanf("%s", s);
		sscanf(s, "%lf", &edge[2*j-1]);
		fprintf(stderr,"\b\r  lower edge of band(%d) = %10.6f        ",j,edge[2*j-1]);
		fprintf(stderr, "\n  upper edge of band(%d) = ?",j);
		scanf("%s", s);
		sscanf(s, "%lf", &edge[2*j]);
		fprintf(stderr,"\b\r  upper edge of band(%d) = %10.6f        ",j,edge[2*j]);
	}
	fprintf(stderr,"\n desired frequency response");
	for(j=1;j<=nbands;j++) {
		fprintf(stderr, "\n  amplitude(%d) = ?",j);
		scanf("%s", s);
		sscanf(s, "%lf", &fx[j]);
		fprintf(stderr,"\b\r  amplitude(%d) = %10.6f        ",j,fx[j]);
	}
	fprintf(stderr,"\n weighting");
	for(j=1;j<=nbands;j++) {
		fprintf(stderr, "\n  weight(%d) = ?",j);
		scanf("%s", s);
		sscanf(s, "%lf", &wtx[j]);
		fprintf(stderr,"\b\r  weight(%d) = %10.6f        ",j,wtx[j]);
	}
	fprintf(stderr,"\n");
	if(jtype==1)
		neg=0;
	else
		neg=1;
	nodd=nfilt/2;
	nodd=nfilt-2*nodd;
	nfcns=nfilt/2;
	if((nodd==1)&&(neg==0))
		nfcns+=1;

/* Set up the dense grid. The number of points in the grid is:              */
/*   (filter length + 1) * grid density / 2                                 */

	grid[1]=edge[1];
	delf=lgrid*nfcns;
	delf=0.5/delf;
	if(neg!=0)
		if(edge[1]<delf)
			grid[1]=delf;
/* SKIP4 */
	j=1;
	l=1;
	lband=1;
	for(;;) {
		fup=edge[l+1];
		for(;;) {
			temp=grid[j];
			des[j]=eff(temp,lband);
			wt[j]=wate(temp,lband);
			grid[++j]=temp+delf;
			if(grid[j]>fup)
				break;
		}
		grid[j-1]=fup;
		des[j-1]=eff(fup,lband);
		wt[j-1]=wate(fup,lband);
		lband++;
		l+=2;
		if(lband>nbands)
			break;
		grid[j]=edge[l];
	}
	ngrid=j-1;
	if(neg==nodd)
		if(grid[ngrid]>(0.5-delf))
			ngrid--;

/* Set up a new approximation problem                                       */
/* which is equivalent to the original problem                              */
/* SKIP9 */
	if(neg>0) {
		if(nodd==1) {
			for(j=1;j<=ngrid;j++) {
				change=sin(2.0*PI*grid[j]);
				des[j]/=change;
				wt[j]*=change;
			}
		}
		else {
			for(j=1;j<=ngrid;j++) {
				change=sin(PI*grid[j]);
				des[j]/=change;
				wt[j]*=change;
			}
		}
	}
	else {
		if(nodd!=1) {
			for(j=1;j<=ngrid;j++) {
				change=cos(PI*grid[j]);
				des[j]/=change;
				wt[j]*=change;
			}
		}
	}

/* Initial guess for the external frequencies                               */
/* -- equally spaced along the grid                                         */
/* SKIPB */
	temp=(double)(ngrid-1)/(double)nfcns;
	for(j=1;j<=nfcns;j++) {
		iext[j]=(j-1)*temp+1;
	}
	iext[nfcns+1]=ngrid;
	nm1=nfcns-1;
	nz=nfcns+1;

/* Call the Remez exchange algorithm to do the approximation problem        */

	remez();

/* Calculate the impulse response                                           */

	if(neg>0) {
		if(nodd==0) {
			h[1]=0.25*alpha[nfcns];
			for(j=2;j<=nm1;j++) {
				h[j]=0.25*(alpha[nz-j]-alpha[nfcns+2-j]);
			}
			h[nfcns]=0.5*alpha[1]-0.25*alpha[2];
		}
		else {
			h[1]=0.25*alpha[nfcns];
			h[2]=0.25*alpha[nm1];
			for(j=3;j<=nm1;j++) {
				h[j]=0.25*(alpha[nz-j]-alpha[nfcns+3-j]);
			}
			h[nfcns]=0.5*alpha[1]-0.25*alpha[3];
			h[nz]=0.0;
		}
	}
	else {
		if(nodd==0) {
			h[1]=0.25*alpha[nfcns];
			for(j=2;j<=nm1;j++) {
				h[j]=0.25*(alpha[nz-j]+alpha[nfcns+2-j]);
			}
			h[nfcns]=0.5*alpha[1]+0.25*alpha[2];
		}
		else {
			for(j=1;j<=nm1;j++) {
				h[j]=0.5*alpha[nz-j];
			}
			h[nfcns]=alpha[1];
		}
	}

/* Program output section                                                   */
/* SKIPF */

	out_put();

}


/* Function to calculate the desired magnitude response                     */
/* as a function of frequency                                               */

double	eff(temp,lband)
double	temp;
int		lband;
{
	if(jtype!=2)
		return(fx[lband]);
	else
		return(fx[lband]*temp);
}


/* Function to calculate the weight function as a function of frequency     */

double	wate(temp,lband)
double	temp;
int		lband;
{
	if(jtype!=2)
		return(wtx[lband]);
	if(fx[lband]>=0.0001)
		return(wtx[lband]/temp);
	return(wtx[lband]);
}


/* Remez exchange                                                           */

remez()
{
	int		j,k,l,itrmax,nz,nzz,niter,nu,nut,nut1,jet,k1,kn,knz,kkk,kup,klow,
			luck,nm1,jm1,jp1,jchnge;

	double	devl,dtemp,dnum,dden,ynz,yy,err,fsh,gtemp,delf,cn,aa,bb,
			ft,xt,xe,comp=0.0;

	itrmax=25;
	devl=-1;
	nz=nfcns+1;
	nzz=nfcns+2;
	niter=0;
STEP1:
	iext[nzz]=ngrid+1;
	niter++;
	if(niter>itrmax) goto STEP2;
	for(j=1;j<=nz;j++) {
		dtemp=grid[iext[j]];
		dtemp=cos(2.0*PI*dtemp);
		x[j]=dtemp;
	}
	jet=(nfcns-1)/15+1;
	for(j=1;j<=nz;j++) {
		ad[j]=d(j,nz,jet);
	}
	dnum=0.0;
	dden=0.0;
	k=1;
	for(j=1;j<=nz;j++) {
		l=iext[j];
		dtemp=ad[j]*des[l];
		dnum+=dtemp;
		dtemp=k*ad[j]/wt[l];
		dden+=dtemp;
		k=-k;
	}
	dev=dnum/dden;
	nu=1;
	if(dev>0) nu=-1;
	dev=-nu*dev;
	k=nu;
	for(j=1;j<=nz;j++) {
		l=iext[j];
		dtemp=k*dev/wt[l];
		y[j]=des[l]+dtemp;
		k=-k;
	}
	if(dev>=devl) goto STEP3;
	printf("\n ***** FAILURE TO CONVERGE *****");
	printf("\n  Probable cause is machine rounding error.");
	printf("\n  The inpulse response may be correct.");
	printf("\n  Check with a frequency response.");
	goto STEP2;
STEP3:
	devl=dev;
	jchnge=0;
	k1=iext[1];
	knz=iext[nz];
	klow=0;
	nut=-nu;
	j=1;

/* Search for hte external frequencies of the best approximation */
STEP4:
	if(j==nzz) ynz=comp;
	if(j>=nzz) goto STEP5;
	kup=iext[j+1];
	l=iext[j]+1;
	nut=-nut;
	if(j==2)
		yy=comp;
	comp=dev;
	if(l>=kup) goto STEP6;
	err=gee(l,nz);
	err=(err-des[l])*wt[l];
	dtemp=nut*err-comp;
	if(dtemp<=0) goto STEP6;
	comp=nut*err;
STEP7:
	l++;
	if(l>=kup) goto STEP8;
	err=gee(l,nz);
	err=(err-des[l])*wt[l];
	dtemp=nut*err-comp;
	if(dtemp<=0) goto STEP8;
	comp=nut*err;
	goto STEP7;
STEP8:
	iext[j++]=l-1;
	klow=l-1;
	jchnge++;
	goto STEP4;
STEP6:
	l--;
STEP9:
	l--;
	if(l<=klow) goto STEPA;
	err=gee(l,nz);
	err=(err-des[l])*wt[l];
	dtemp=nut*err-comp;
	if(dtemp>0) goto STEPB;
	if(jchnge<=0) goto STEP9;
	goto STEPC;
STEPB:
	comp=nut*err;
STEPD:
	l--;
	if(l<=klow) goto STEPE;
	err=gee(l,nz);
	err=(err-des[l])*wt[l];
	dtemp=nut*err-comp;
	if(dtemp<=0) goto STEPE;
	comp=nut*err;
	goto STEPD;
STEPE:
	klow=iext[j];
	iext[j++]=l+1;
	jchnge++;
	goto STEP4;
STEPA:
	l=iext[j]+1;
	if(jchnge>0) goto STEP8;
STEPF:
	l++;
	if(l>=kup) goto STEPC;
	err=gee(l,nz);
	err=(err-des[l])*wt[l];
	dtemp=nut*err-comp;
	if(dtemp<=0) goto STEPF;
	comp=nut*err;
	goto STEP7;
STEPC:
	klow=iext[j++];
	goto STEP4;
STEP5:
	if(j>nzz) goto STEPG;
	if(k1>iext[1])
		k1=iext[1];
	if(knz<iext[nz])
		knz=iext[nz];
	nut1=nut;
	nut=-nu;
	l=0;
	kup=k1;
	comp=ynz*1.00001;
	luck=1;
STEPH:
	l++;
	if(l>=kup) goto STEPI;
	err=gee(l,nz);
	err=(err-des[l])*wt[l];
	dtemp=nut*err-comp;
	if(dtemp<=0) goto STEPH;
	comp=nut*err;
	j=nzz;
	goto STEP7;
STEPI:
	luck=6;
	goto STEPJ;
STEPG:
	if(luck>9) goto STEPK;
	if(comp>yy) yy=comp;
	k1=iext[nzz];
STEPJ:
	l=ngrid+1;
	klow=knz;
	nut=-nut1;
	comp=yy*1.00001;
STEPL:
	l--;
	if(l<=klow) goto STEPM;
	err=gee(l,nz);
	err=(err-des[l])*wt[l];
	dtemp=nut*err-comp;
	if(dtemp<=0) goto STEPL;
	j=nzz;
	comp=nut*err;
	luck+=10;
	goto STEPD;
STEPM:
	if(luck==6) goto STEPN;
	for(j=1;j<=nfcns;j++) {
		iext[nzz-j]=iext[nz-j];
	}
	iext[1]=k1;
	goto STEP1;
STEPK:
	kn=iext[nzz];
	for(j=1;j<=nfcns;j++) {
		iext[j]=iext[j+1];
	}
	iext[nz]=kn;
	goto STEP1;
STEPN:
	if(jchnge>0) goto STEP1;

/* Calculation of the coefficients of the best approximation                */
/* using the inverse discrete fourier transform                             */

STEP2:
	nm1=nfcns-1;
	fsh=0.000001;
	gtemp=grid[1];
	x[nzz]=-2.0;
	cn=2*nfcns-1;
	delf=1.0/cn;
	l=1;
	kkk=0;
/*	if((grid[1]<.01)&&(grid[ngrid]>0.49)) kkk=1;*/
	if((edge[1]==0.0)&&(edge[2*nbands]==0.5)) kkk=1;
	if(nfcns<=3) kkk=1;
	if(kkk==1) goto STEPO;
	dtemp=cos(2.0*PI*grid[1]);
	dnum=cos(2.0*PI*grid[ngrid]);
	aa=2.0/(dtemp-dnum);
	bb=-(dtemp+dnum)/(dtemp-dnum);
STEPO:
	for(j=1;j<=nfcns;j++) {
		ft=(j-1)*delf;
		xt=cos(2.0*PI*ft);
		if(kkk==1) goto STEPP;
		xt=(xt-bb)/aa;
		ft=acos(xt)/(2.0*PI);
	STEPP:
		xe=x[l];
		if(xt>xe) goto STEPQ;
		if((xe-xt)<fsh) goto STEPR;
		l++;
		goto STEPP;
	STEPR:
		a[j]=y[l];
		goto STEPS;
	STEPQ:
		if((xt-xe)<fsh) goto STEPR;
		grid[1]=ft;
		a[j]=gee(1,nz);
	STEPS:
		if(l>1) l--;
	}
	grid[1]=gtemp;
	dden=2.0*PI/cn;
	for(j=1;j<=nfcns;j++) {
		dtemp=0.0;
		dnum=(j-1)*dden;
		if(nm1<1) goto STEPT;
		for(k=1;k<=nm1;k++) {
			dtemp+=a[k+1]*cos(dnum*k);
		}
	STEPT:
		dtemp=2.0*dtemp+a[1];
		alpha[j]=dtemp;
	}
	for(j=2;j<=nfcns;j++) {
		alpha[j]=2.0*alpha[j]/cn;
	}
	alpha[1]=alpha[1]/cn;
	if(kkk==1) goto STEPU;
	p[1]=2.0*alpha[nfcns]*bb+alpha[nm1];
	p[2]=2.0*aa*alpha[nfcns];
	q[1]=alpha[nfcns-2]-alpha[nfcns];
	for(j=2;j<=nm1;j++) {
		if(j>=nm1) {
			aa*=0.5;
			bb*=0.5;
		}
		p[j+1]=0.0;
		for(k=1;k<=j;k++) {
			a[k]=p[k];
			p[k]=2.0*bb*a[k];
		}
		p[2]+=a[1]*2.0*aa;
		jm1=j-1;
		for(k=1;k<=jm1;k++) {
			p[k]+=q[k]+aa*a[k+1];
		}
		jp1=j+1;
		for(k=3;k<=jp1;k++) {
			p[k]+=aa*a[k-1];
		}
		if(j!=nm1) {
			for(k=1;k<=j;k++) {
				q[k]=-a[k];
			}
			q[1]+=alpha[nfcns-1-j];
		}
	}
	for(j=1;j<=nfcns;j++) {
		alpha[j]=p[j];
	}
STEPU:
	if(nfcns<=3) {
		alpha[nfcns+1]=0.0;
		alpha[nfcns+2]=0.0;
	}
}


/* Function to calaulate the lagrange interpolation                         */
/* coefficients for use in the function 'gee'.                              */

double d(k,n,m)
int	k,n,m;
{
	int		j,l;
	double	dd,qq;

	dd=1.0;
	qq=x[k];
	for(l=1;l<=m;l++) {
		for(j=l;j<=n;j+=m) {
			if(j!=k) {
				dd=2.0*dd*(qq-x[j]);
			}
		}
	}
	dd=1.0/dd;
	return(dd);
}

/* Function to evaluate the frequency response using the                    */
/* lagrange interpolation formula in the barycentric form                   */

double gee(k,n)
int	k,n;
{
	int		j;
	double	pp,c,dd,xf;

	pp=0.0;
	xf=grid[k];
	xf=cos(2.0*PI*xf);
	dd=0.0;
	for(j=1;j<=n;j++) {
		c=xf-x[j];
		c=ad[j]/c;
		dd+=c;
		pp+=c*y[j];
	}
	return(pp/dd);
}


out_put()
{
	wr_spec(stderr);

	fprintf(stderr, "\n Save into a file (y/n) ?");
	scanf("%s", s);
	if(toupper(s[0])=='Y') {
		fprintf(stderr, "\n Filename to write (append) ?");
		scanf("%s", filename);
		if(fp_w=fopen(filename,"a")) {
			fprintf(stderr, "\n Do you need c source  'double h[]' (y/n) ?");
			scanf("%s", s);
			if(toupper(s[0])=='Y')
				c_src();
			fprintf(stderr, "\n Do you need asm source for TMS320  ' .wordn ' (y/n) ?");
			scanf("%s", s);
			if(toupper(s[0])=='Y')
				asm_src32();
			fprintf(stderr, "\n Do you need asm source for DSP56k  ' dc ' (y/n) ?");
			scanf("%s", s);
			if(toupper(s[0])=='Y')
				asm_src56();
			fprintf(stderr, "\n Do you need frequency response (y/n) ?");
			scanf("%s", s);
			if(toupper(s[0])=='Y')
				fresp();
			fclose(fp_w);
		}
		else {
			fprintf(stderr, " Can not open %s.",filename);
		}
	}
}


wr_spec(wp)
FILE	*wp;
{
	int		j,k,kup;

	if(jtype==1)
		fprintf(wp, "\n; passband/stopband filter");
	else if(jtype==2)
		fprintf(wp, "\n; differentiator");
	else if(jtype==3)
		fprintf(wp, "\n; hilbert transformer");
	fprintf(wp, "\n; filter length = %d",nfilt);
	for(k=1;k<=nbands;k+=4) {
		kup=k+3;
		if(kup>nbands)
			kup=nbands;
		fprintf(wp, "\n;                    ");
		for(j=k;j<=kup;j++)
			fprintf(wp, "      band%3d",j);
		fprintf(wp, "\n; lower edge frequency:");
		for(j=k;j<=kup;j++)
			fprintf(wp, " %10.6f  ",edge[2*j-1]);
		fprintf(wp, "\n; upper edge frequency:");
		for(j=k;j<=kup;j++)
			fprintf(wp, " %10.6f  ",edge[2*j]);
		if(jtype!=2) {
			fprintf(wp, "\n; desired f-response:  ");
			for(j=k;j<=kup;j++)
				fprintf(wp, " %10.6f  ",fx[j]);
		}
		else {
			fprintf(wp, "\n; desired slope:       ");
			for(j=k;j<=kup;j++)
				fprintf(wp, " %10.6f  ",fx[j]);
		}
		fprintf(wp, "\n; weighting:           ");
		for(j=k;j<=kup;j++)
			fprintf(wp, " %10.6f  ",wtx[j]);
		for(j=k;j<=kup;j++)
			deviat[j]=dev/wtx[j];
		fprintf(wp, "\n; deviation:           ");
		for(j=k;j<=kup;j++)
			fprintf(wp, " %10.6f  ",deviat[j]);
		for(j=k;j<=kup;j++)
			deviat[j]=20.0*(log(deviat[j]+fx[j]))/ln10;
		fprintf(wp, "\n; deviation (dB):      ");
		for(j=k;j<=kup;j++)
			fprintf(wp, " %10.6f  ",deviat[j]);
		fprintf(wp, "\n");
	}
}


c_src()
{
	int		j;

	fprintf(fp_w,"\ndouble	h[] = { ");
	for(j=1;j<nfcns;j++) {
		hr = h[nfcns-j+1];
		fprintf(fp_w," %12.8f,",hr);
		if(j%4==0)  fprintf(fp_w,"\n		        ");
	}
		hr = h[nfcns-j+1];
		fprintf(fp_w," %12.8f",hr);
	fprintf(fp_w," };\n/*");
	wr_spec(fp_w);
	fprintf(fp_w,"*/\n");
}


asm_src32()
{
	int		j,hi;

	wr_spec(fp_w);
	for(j=1;j<=nfcns;j++) {
		hr = h[nfcns-j+1];
		hi = (double)0x8000*hr;
		fprintf(fp_w,"\n	.wordn	$%04X	; %3d: %12.8f",hi,j-1,hr);
	}
	fprintf(fp_w,"\n");
}


asm_src56()
{
	int		j,hi;

	wr_spec(fp_w);
	for(j=1;j<=nfcns;j++) {
		hr = h[nfcns-j+1];
		fprintf(fp_w,"\n	dc	%12.8f	; %3d",hr,j-1);
	}
	fprintf(fp_w,"\n");
}


fresp()
{
	int		i,k,flag=0;
	double	fr,mh,yr,ya,yl,ymax=0.0;

	for(i=0;i<=50;i++) {
		fr = 0.01*(double)i;
		mh = (double)(nfilt-1)/2.0;
		if(jtype!=3) {
			if(nodd==0) {
				yr = 0;
				for(k=0;k<nfcns;k++) {
					yr += h[k+1]*cos((mh-k)*2.0*PI*fr);
				}
				yr *= 2.0;
			}
			else {
				yr = 0;
				for(k=0;k<nfcns;k++) {
					yr += h[k+1]*cos((mh-k)*2.0*PI*fr);
				}
				yr *= 2.0;
				if(neg==0)
					yr -= h[nfcns];
			}
		}
		else {
			if(nodd==0) {
				yr = 0;
				for(k=0;k<nfcns;k++) {
					yr += h[k+1]*sin((mh-k)*2.0*PI*fr);
				}
				yr *= 2.0;
			}
			else {
				yr = 0;
				for(k=0;k<nfcns;k++) {
					yr += h[k+1]*sin((mh-k)*2.0*PI*fr);
				}
				yr *= 2.0;
			}
		}
		if(yr<0) {
			ya = -yr;
			flag = 1;
		}
		else
			ya = yr;
		if((ya>ymax)&&(flag>0))
			ymax = ya;
		if(ya<0.000001)
			ya = 0.000001;
		yl = 20*log(ya)/ln10;
		fprintf(fp_w,"\n %7.3f  %10.6f  %7.2f",fr,yr,yl);
	}
	if(ymax>0.000001) {
		yl = 20*log(ymax)/ln10;
		fprintf(fp_w,"\n  ymax=%8.4f  %7.2f",ymax,yl);
	}
}

