import FWCore.ParameterSet.Config as cms


def enableMinPtHatCut(process,genTypePtHatRange):
    if genTypePtHatRange=='NSD_0_to_5':
        print "Min pT_hat cut enable"
        process.genSpectAna.pthatCut=cms.untracked.double(5.0)
    if genTypePtHatRange=='NSD_0_to_10':
        print "Min pT_hat cut enable"
        process.genSpectAna.pthatCut=cms.untracked.double(10.0)
    if genTypePtHatRange=='NSD_0_to_15':
        print "Min pT_hat cut enable"
        process.genSpectAna.pthatCut=cms.untracked.double(15.0)
    if genTypePtHatRange=='NSD_0_to_20':
        print "Min pT_hat cut enable"
        process.genSpectAna.pthatCut=cms.untracked.double(20.0)
    if genTypePtHatRange=='ENSD_0_to_5':
        print "Min pT_hat cut enable"
        process.genSpectAna.pthatCut=cms.untracked.double(5.0)
    if genTypePtHatRange=='ENSD_0_to_10':
        print "Min pT_hat cut enable"
        process.genSpectAna.pthatCut=cms.untracked.double(10.0)
    if genTypePtHatRange=='ENSD_0_to_15':
        print "Min pT_hat cut enable"
        process.genSpectAna.pthatCut=cms.untracked.double(15.0)
    if genTypePtHatRange=='ENSD_0_to_20':
        print "Min pT_hat cut enable"
        process.genSpectAna.pthatCut=cms.untracked.double(20.0)
    if genTypePtHatRange=='ENSD_0_to_30':
        print "Min pT_hat cut enable"
        process.genSpectAna.pthatCut=cms.untracked.double(30.0)
    if genTypePtHatRange=='MB_0_to_5':
        print "Min pT_hat cut enable"
        process.genSpectAna.pthatCut=cms.untracked.double(5.0)
    if genTypePtHatRange=='MB_0_to_10':
        print "Min pT_hat cut enable"
        process.genSpectAna.pthatCut=cms.untracked.double(10.0)
    if genTypePtHatRange=='MB_0_to_15':
        print "Min pT_hat cut enable"
        process.genSpectAna.pthatCut=cms.untracked.double(15.0)
    if genTypePtHatRange=='MB_0_to_20':
        print "Min pT_hat cut enable"
        process.genSpectAna.pthatCut=cms.untracked.double(20.0)
    return process


# Check this values for various tunes!
def getPy6ProcXsection(genTypePtHatRange):
    para = {
        'TOP':4.552E-08,
        'NSD_0_to_5':4.130E+01,
#        '7TeV_NSD_0_to_5':4.844E+01,#in fact this is the total sigma
#        'AMBT1_7TeV_NSD_0_to_5':4.844E+01,#total sigma; yes, it's the same
        '7TeV_NSD_0_to_5':8.145,#other pThat bins subtracted
        '5TeV_NSD_0_to_5':1.880E+01,# 4.573E+01,other bins were subtracted
        '5TeV_NSD_0_to_5_TOTALXSEC':4.573E+01,
        'AMBT1_7TeV_NSD_0_to_5':8.145,#NEGATIVE NUMBER??? Copy of ProQ20
        'NSD_5_to_10':1.155E+01,
        '7TeV_NSD_5_to_10':3.652E+01,
        '5TeV_NSD_5_to_10':2.457E+01,
        'AMBT1_7TeV_NSD_5_to_10':4.385E+01,
        'NSD_10_to_20':9.073E-01,
        '7TeV_NSD_10_to_20':3.489E+00,
        '5TeV_NSD_10_to_20':2.192E+00,
        'AMBT1_7TeV_NSD_10_to_20':4.478E+00,
        'NSD_0_to_10':4.130E+01,
        '5TeV_MB_0_to_10':6.783E+01,#without subtraction: 6.783E+01; MB_10_to_inf: 6.782D+01... ; assume the full...
        '5TeV_MB_0_to_20':6.783E+01,#see above...
        'AMBT1_5TeV_MB_0_to_20':6.786E+01,#see above...
        'Z2_5TeV_MB_0_to_20':6.784E+01,
        'D6T_5TeV_MB_0_to_20':6.781E+01,
        'NSD_0_to_10':4.130E+01,
        'AMBT1_7TeV_NSD_0_to_10':4.844E+01,
        'NSD_0_to_15':4.130E+01,
        '7TeV_NSD_0_to_15':4.844E+01,
        'AMBT1_7TeV_NSD_0_to_15':4.844E+01,
        'NSD_0_to_20':4.130E+01,
        '7TeV_NSD_0_to_20':4.844E+01,
        '5500GeV_NSD_0_to_20':4.626E+01, #Other pthat bins subtracted on 02.09.12
        'AMBT1_7TeV_NSD_0_to_20':4.844E+01,
        'NSD_15_to_20':1.373E-01,
        '7TeV_NSD_15_to_20':5.653E-01,
        'AMBT1_7TeV_NSD_15_to_20':7.555E-01,
        'NSD_20_to_30':4.903E-02,
        '7TeV_NSD_20_to_30':2.285E-01,
        '5500GeV_NSD_20_to_30':1.577E-01,
        '5TeV_NSD_20_to_30':1.344E-01,
        'AMBT1_5TeV_NSD_20_to_30':1.858E-01,
        'Z2_5TeV_NSD_20_to_30':1.392E-01,
        'D6T_5TeV_NSD_20_to_30':1.406E-01,
        'AMBT1_7TeV_NSD_20_to_30':3.084E-01,
        'NSD_30_to_50':9.366E-03,
        '7TeV_NSD_30_to_50':5.112E-02,
        '5500GeV_NSD_30_to_50':3.353E-02,
        '5TeV_NSD_30_to_50':2.876E-02,
        'AMBT1_5TeV_NSD_30_to_50':4.044E-02,
        'Z2_5TeV_NSD_30_to_50':2.991E-02,
        'D6T_5TeV_NSD_30_to_50':2.989E-02,
        'AMBT1_7TeV_NSD_30_to_50':7.038E-02,
        '7TeV_NSD_30_to_inf':5.817E-02,
        'AMBT1_7TeV_NSD_30_to_inf':7.988E-02,
        'NSD_50_to_80':9.071E-04,
        '7TeV_NSD_50_to_80':6.077E-03,
        '5500GeV_NSD_50_to_80':3.850E-03,
        '5TeV_NSD_50_to_80':3.178E-03,
        'AMBT1_5TeV_NSD_50_to_80':4.498E-03,
        'Z2_5TeV_NSD_50_to_80':3.348E-03,
        'D6T_5TeV_NSD_50_to_80':3.329E-03,
        'AMBT1_7TeV_NSD_50_to_80':8.523E-03,
        'NSD_80_to_inf':9.925E-05,
        '7TeV_NSD_80_to_inf':8.908E-04,
        'AMBT1_7TeV_NSD_80_to_inf':1.261E-03,
        'NSD_80_to_120':8.951E-05,
        '7TeV_NSD_80_to_120':7.606E-04,
        '5500GeV_NSD_80_to_120':4.537E-04,
        '5TeV_NSD_80_to_120':3.711E-04,
        'AMBT1_5TeV_NSD_80_to_120':5.211E-04,
        'Z2_5TeV_NSD_80_to_120':3.810E-04,
        'D6T_5TeV_NSD_80_to_120':3.780E-04,
        'AMBT1_7TeV_NSD_80_to_120':1.062E-03,
        'NSD_120_to_170':9.929E-06,
        '7TeV_NSD_120_to_170':1.136E-04,
        '5500GeV_NSD_120_to_170':6.351E-05,
        '5TeV_NSD_120_to_170':5.119E-05,
        'AMBT1_5TeV_NSD_120_to_170':6.874E-05,
        'Z2_5TeV_NSD_120_to_170':5.205E-05,
        'D6T_5TeV_NSD_120_to_170':5.175E-05,
        'AMBT1_7TeV_NSD_120_to_170':1.559E-04,
        'NSD_170_to_230':1.324E-06,
        '7TeV_NSD_170_to_230':2.010E-05,
        '5500GeV_NSD_170_to_230':1.081E-05,
        '5TeV_NSD_170_to_230':8.388E-06,
        'AMBT1_5TeV_NSD_170_to_230':1.085E-05,
        'Z2_5TeV_NSD_170_to_230':8.236E-06,
        'D6T_5TeV_NSD_170_to_230':8.299E-06,
        'AMBT1_7TeV_NSD_170_to_230':2.694E-05,
        'NSD_230_to_300':1.906E-07,
        '7TeV_NSD_230_to_300':4.160E-06,
        '5500GeV_NSD_230_to_300':2.075E-06,
        '5TeV_NSD_230_to_300':1.578E-06, #Fixed at 28.08.13
        'AMBT1_5TeV_NSD_230_to_300':1.939E-06, #Fixed at 28.08.13
        'Z2_5TeV_NSD_230_to_300':1.501E-06,
        'D6T_5TeV_NSD_230_to_300':1.521E-06,
        'AMBT1_7TeV_NSD_230_to_300':5.431E-06,
        'NSD_300_to_380':2.960E-08,
        '7TeV_NSD_300_to_380':9.661E-07,
        '5500GeV_NSD_300_to_380':4.507E-07,
        '5TeV_NSD_300_to_380':3.311E-07,
        'AMBT1_5TeV_NSD_300_to_380':3.896E-07,
        'Z2_5TeV_NSD_300_to_380':3.165E-07,
        'D6T_5TeV_NSD_300_to_380':3.143E-07,
        'AMBT1_7TeV_NSD_300_to_380':1.209E-06,
        'NSD_380_to_470':4.469E-09,
        '7TeV_NSD_380_to_470':2.454E-07,
        'AMBT1_7TeV_NSD_380_to_470':2.959E-07,
        'NSD_380_to_inf':5.208E-09,
        '7TeV_NSD_380_to_inf':3.383E-07,
        '5500GeV_NSD_380_to_inf':1.402E-07,
        '5TeV_NSD_380_to_inf':9.841E-08,
        'AMBT1_5TeV_NSD_380_to_inf':1.101E-07,
        'Z2_5TeV_NSD_380_to_inf':9.051E-08,
        'D6T_5TeV_NSD_380_to_inf':9.176E-08,
      #  'Z2_5TeV_NSD_380_to_inf':9.073E-08,
        'AMBT1_7TeV_NSD_380_to_inf':4.028E-07,
        'NSD_470_to_inf':7.241E-10,
        '7TeV_NSD_470_to_inf':9.354E-08,
        'AMBT1_7TeV_NSD_470_to_inf':1.072E-07,
        'NSD_470_to_570':6.365E-10,
        '7TeV_NSD_470_to_570':6.641E-08,
        'AMBT1_7TeV_NSD_470_to_570':7.746E-08,
        'NSD_570_to_670':7.524E-11,
        '7TeV_NSD_570_to_670':1.813E-08,
        'AMBT1_7TeV_NSD_570_to_670':2.043E-08,
        'NSD_670_to_800':9.318E-12,
        '7TeV_NSD_670_to_800':6.511E-09,
        'AMBT1_7TeV_NSD_670_to_800':7.088E-09,
        'NSD_800_to_930':4.723E-13,
        '7TeV_NSD_800_to_930':1.684E-09,
        'AMBT1_7TeV_NSD_800_to_930':1.777E-09,
        'NSD_930_to_1000':1.296E-14,
        '7TeV_NSD_930_to_1000':3.301E-10,
        'AMBT1_7TeV_NSD_930_to_1000':3.447E-10,
        'NSD_930_to_inf':1.446E-14,
        '7TeV_NSD_930_to_inf':7.082E-10,
        'AMBT1_7TeV_NSD_930_to_inf':7.347E-10,
        'NSD_1000_to_1100':1.536E-15,
        '7TeV_NSD_1000_to_1100':2.215E-10,
        'AMBT1_7TeV_NSD_1000_to_1100':2.258E-10,
        'NSD_1100_to_1200':3.136E-17,
        '7TeV_NSD_1100_to_1200':9.100E-11,
        'AMBT1_7TeV_NSD_1100_to_1200':9.355E-11,
        '7TeV_NSD_1200_to_1400':5.398E-11,
        'AMBT1_7TeV_NSD_1200_to_1400':5.650E-11,
        '7TeV_NSD_1400_to_1600':9.996E-12,
        'AMBT1_7TeV_NSD_1400_to_1600':1.055E-11,
        '7TeV_NSD_1600_to_1800':1.860E-12,
        'AMBT1_7TeV_NSD_1600_to_1800':2.013E-12,
        '7TeV_NSD_1800_to_2000':3.235E-13,
        'AMBT1_7TeV_NSD_1800_to_2000':3.587E-13,
        '7TeV_NSD_2000_to_2200':5.197E-14,
        'AMBT1_7TeV_NSD_2000_to_2200':5.943E-14,
        '7TeV_NSD_2200_to_2400':6.860E-15,
        'AMBT1_7TeV_NSD_2200_to_2400':8.377E-15,
        '7TeV_NSD_2400_to_2600':7.247E-16,
        'AMBT1_7TeV_NSD_2400_to_2600':9.518E-16,
        '7TeV_NSD_2600_to_2800':5.280E-17,
        'AMBT1_7TeV_NSD_2600_to_2800':7.639E-17,
        '7TeV_NSD_2800_to_3000':2.129E-18,
        'AMBT1_7TeV_NSD_2800_to_2900':2.988E-18,
        'AMBT1_7TeV_NSD_2800_to_3000':3.454E-18,
        '7TeV_NSD_3000_to_3200':3.329E-20,
        'AMBT1_7TeV_NSD_3000_to_3200':5.481E-20,
        '7TeV_NSD_3200_to_inf':7.349E-23,
        'AMBT1_7TeV_NSD_2900_to_inf':5.253E-19,
        'NSD_1200_to_inf':1.405E-19,
        '7TeV_NSD_1200_to_inf':6.682E-11,
        '7TeV_NSD_0_to_inf':4.844E+01
        }
#    print 'PYTHIA process xsection = %s mb' % para[genTypePtHatRange]
    return para[genTypePtHatRange]
         
