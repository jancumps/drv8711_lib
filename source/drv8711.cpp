module;

#include <cstdint>

import stepper_driver;

export module drv8711;
export namespace drv8711 {

struct ctrl {
                            // address 14-12
    unsigned int dtime;     // 11-10
    unsigned int isgain;    // 9-8
    unsigned int exstall;   // 7
    unsigned int mode;      // 6-3
    unsigned int rstep;     // 2
    unsigned int rdir;      // 1
    unsigned int enbl;      // 0
    inline operator uint16_t() const {
        return (0x0000 << 12) | (dtime << 10) | (isgain << 8) |(exstall << 7) | (mode << 3) | (rstep << 2) | (rdir << 1) | (enbl);
    }
};
 
struct torque {
                            // address 14-12
                            // 11
    unsigned int simplth;   // 10-8
    unsigned int torque;    // 7-0
    inline operator uint16_t() const {
        return (0x0001 << 12) | (simplth << 8) | torque;
    }
};
 
struct off {
                            // address 14-12
                            // 11-9
    unsigned int pwmmode;   // 8
    unsigned int toff;      // 7-0
    inline operator uint16_t() const {
        return (0x0002 << 12) | (pwmmode << 8) | toff;
    }
};
 
struct blank {
                            // address 14-12
                            // 11-9
    unsigned int abt;       // 8
    unsigned int tblank;    // 7-0
    inline operator uint16_t() const {
        return (0x0003 << 12) | (abt << 8) | tblank;
    }
};
 
struct decay {
                            // address 14-12
                            // 11
    unsigned int decmod;    // 10-8
    unsigned int tdecay;    // 7-0
    inline operator uint16_t() const {
        return (0x0004 << 12) | (decmod << 8) | tdecay;
    }
};
 
struct stall {
                            // address 14-12
    unsigned int vdiv;      // 11-10
    unsigned int sdcnt;     // 9-8
    unsigned int sdthr;     // 7-0
    inline operator uint16_t() const {
        return (0x0005 << 12) | (vdiv << 10) | (sdcnt << 8) | sdthr;
    }
};
 
struct drive {
                            // address 14-12
    unsigned int idrivep;   // 11-10
    unsigned int idriven;   // 9-8
    unsigned int tdrivep;   // 7-6
    unsigned int tdriven;   // 5-4
    unsigned int ocpdeg;    // 3-2
    unsigned int ocpth;     // 1-0
    inline operator uint16_t() const {
        return (0x0006 << 12) | (idrivep << 10) | (idriven << 8) | (tdrivep << 6) | (tdriven << 4) | (ocpdeg << 2) | (ocpth);
    }
};
 
struct status {
                            // address 14-12
                            // 11-8
    unsigned int stdlat;    // 7
    unsigned int std;       // 6
    unsigned int uvlo;      // 5
    unsigned int bpdf;      // 4
    unsigned int apdf;      // 3
    unsigned int bocp;      // 2
    unsigned int aocp;      // 1
    unsigned int ots;       // 0
    inline operator uint16_t() const {
        return (0x0007 << 12) | (stdlat << 7) | (std << 6) | (uvlo << 5) | (bpdf << 4) | (apdf << 3) | (bocp << 2) | (aocp << 1) | (ots);
    }
};

class drv8711_driver : public stepper_driver::stepper_driver {
public:
protected:
    virtual unsigned int microsteps_mode(unsigned int microsteps) {
        unsigned int mode = true;
        switch (microsteps) {
        case 1:
            mode = 0x0000;
            break;
        case 2:
            mode = 0x0001;
            break;
        case 4:
            mode = 0x0002;
            break;
        case 8:
            mode = 0x0003;
            break;
        case 16:
            mode = 0x0004;
            break;
        case 32:
            mode = 0x0005;
            break;
        case 64:
            mode = 0x0006;
            break;
        case 128:
            mode = 0x0007;
            break;
        case 256:
            mode = 0x0008;
            break;
        default:
            mode = 0x0000;
        }
        return mode;
    }
private:
    virtual void write(uint16_t reg) = 0;
    virtual void init_spi() = 0;
    virtual void init_gpio() = 0;
    virtual void init_registers() = 0;
};

} // namespace drv8711