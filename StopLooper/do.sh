#!/bin/bash

make -j 12 || return $?


# 2017 Data

# INDIR=/nfs-7/userdata/haweber/stopbabiesInteractive/2017_5p8fbinv
# INDIR=/nfs-7/userdata/haweber/tupler_babies/merged/Stop_1l/v2017/output/
INDIR=/nfs-7/userdata/sicheng/stopbabies/merged_v25_7
OUTDIR=output/temp
# OUTDIR=output/data2017_rwgtd
LOGDIR=logs

mkdir -p ${OUTDIR}
mkdir -p ${LOGDIR}

# declare -a Samples=(data_2017B data_2017C data_2017D data_2017E data_2017F)
declare -a Samples=(data_2017D)

# for SAMPLE in ${Samples[@]}; do
#     # ./runStopLooper ${INDIR} ${SAMPLE} ${OUTDIR}
#     echo ./runStopLooper ${INDIR} ${SAMPLE} ${OUTDIR} '>&' ${LOGDIR}/log_${SAMPLE}.txt
#     eval "nohup nice -n -10 ./runStopLooper ${INDIR} ${SAMPLE} ${OUTDIR} >& ${LOGDIR}/log_${SAMPLE}.txt &"
# done

# 2017 MC test

INDIR=/nfs-7/userdata/sicheng/stopbabies/merged_v25_4
# INDIR=/hadoop/cms/store/user/sicheng/ProjectMetis/stopBaby_TTJets_amcnlo_v25_8/merged
OUTDIR=output/temp
# OUTDIR=output/samples2016

mkdir -p ${OUTDIR}
mkdir -p ${LOGDIR}

# declare -a Samples=(TTJets W2Jets W3Jets W4Jets)
declare -a Samples=(TTJets)
# declare -a Samples=(merged_TTJets)

# for SAMPLE in ${Samples[@]}; do
#     ./runStopLooper ${INDIR} ${SAMPLE} ${OUTDIR}
#     # echo ./runStopLooper ${INDIR} ${SAMPLE} ${OUTDIR}
#     # eval "nohup nice -n -10 ./runStopLooper ${INDIR} ${SAMPLE} ${OUTDIR} >& ${LOGDIR}/log_${SAMPLE}.txt &"
# done

# 2016 data
# INDIR=/nfs-7/userdata/stopRun2/analysis2016_SUS-16-051_35p9fbinv/v24/skim
INDIR=/nfs-7/userdata/sicheng/stopbabies/skimmed_v25_10
OUTDIR=output/newbin1_120ifb

mkdir -p ${OUTDIR}
mkdir -p ${LOGDIR}

# declare -a Samples=(all_2016)
declare -a Samples=(data_2016B data_2016C data_2016D data_2016E data_2016F data_2016G data_2016H)

for SAMPLE in ${Samples[@]}; do
    # ./runStopLooper ${INDIR} ${SAMPLE} ${OUTDIR}
    echo ./runStopLooper ${INDIR} ${SAMPLE} ${OUTDIR} '>&' ${LOGDIR}/log_${SAMPLE}.txt
    eval "nohup nice -n -10 ./runStopLooper ${INDIR} ${SAMPLE} ${OUTDIR} >& ${LOGDIR}/log_${SAMPLE}.txt &"
done

# 2016 MC

# INDIR=/nfs-7/userdata/stopRun2/analysis2016_SUS-16-051_35p9fbinv/v22/skim
# declare -a Samples=()
# Samples+=( ttbar_diLept  )    # ttbar
# Samples+=( ttbar_singleLeptFromT_madgraph_pythia8_ext1 ttbar_singleLeptFromTbar_madgraph_pythia8_ext1 )    # ttbar
# Samples+=( t_sch_4f t_tch_4f tbar_tch t_tW_5f t_tbarW_5f ) # singleT
# Samples+=( W1Jets W2Jets W3Jets W4JetsToLNu_madgraph_pythia8_25ns DYJets )            # Vjets : Wjets + DY
# Samples+=( ttWJets ttZJets WW WZ ZZ )                      # rare  : ttV + diboson
# Samples+=( Signal_T2tt )

# INDIR=/nfs-7/userdata/sicheng/stopbabies/merged_v25_9
INDIR=/nfs-7/userdata/sicheng/stopbabies/skimmed_v25_9
# OUTDIR=output/temp

mkdir -p ${OUTDIR}
mkdir -p ${LOGDIR}

declare -a Samples=()
Samples+=( ttbar_diLept ttbar_singleLeptFromT_madgraph ttbar_singleLeptFromTbar_madgraph )    # ttbar
Samples+=( t_tW_top t_tW_antitop )      # singleT
Samples+=( W1Jets W2Jets W3Jets W4Jets)       # Vjets : Wjets + DY
Samples+=( TTZToLLNuNu WZTo1L3Nu )            # rare  : ttV + diboson

for SAMPLE in ${Samples[@]}; do
    # ./runStopLooper ${INDIR} ${SAMPLE} ${OUTDIR}
    echo ./runStopLooper ${INDIR} ${SAMPLE} ${OUTDIR} '>&' ${LOGDIR}/log_${SAMPLE}.txt
    eval "nohup nice -n -10 ./runStopLooper ${INDIR} ${SAMPLE} ${OUTDIR} >& ${LOGDIR}/log_${SAMPLE}.txt &"
done


# 2016 signal
INDIR=/nfs-7/userdata/sicheng/stopbabies/skimmed_v25_9
# INDIR=/nfs-7/userdata/stopRun2/analysis2016_SUS-16-051_35p9fbinv/v22/skim
# OUTDIR=output/temp14

mkdir -p ${OUTDIR}
mkdir -p ${LOGDIR}

declare -a Samples=()
Samples+=( SMS_T2tt_mStop_400to1200_madgraph_0 SMS_T2tt_mStop_400to1200_madgraph_1 SMS_T2tt_mStop_400to1200_madgraph_2 )
Samples+=( SMS_T2tt_mStop_400to1200_madgraph_3 SMS_T2tt_mStop_400to1200_madgraph_4 SMS_T2tt_mStop_400to1200_madgraph_5 )
Samples+=( SMS_T2tt_mStop_400to1200_madgraph_6 SMS_T2tt_mStop_400to1200_madgraph_7 )
Samples+=( SMS_T2bW_madgraph_0 SMS_T2bW_madgraph_1 SMS_T2bW_madgraph_2 )
Samples+=( SMS_T2bW_madgraph_3 SMS_T2bW_madgraph_4 SMS_T2bW_madgraph_5 )
Samples+=( SMS_T2bW_madgraph_6 SMS_T2bW_madgraph_7 )
Samples+=( SMS_T2bt_madgraph_0 SMS_T2bt_madgraph_1 SMS_T2bt_madgraph_2 )
Samples+=( SMS_T2bt_madgraph_3 SMS_T2bt_madgraph_4 SMS_T2bt_madgraph_5 )
# Samples+=( Signal_T2tt Signal_T2bW Signal_T2tb )

for SAMPLE in ${Samples[@]}; do
    echo ./runStopLooper ${INDIR} ${SAMPLE} ${OUTDIR} '>&' ${LOGDIR}/log_${SAMPLE}.txt
    eval "nohup nice -n -10 ./runStopLooper ${INDIR} ${SAMPLE} ${OUTDIR} >& ${LOGDIR}/log_${SAMPLE}.txt &"
done

# Monitor the running
while : ; do
    sleep 5
    RunningJobs=`jobs | grep runStopLooper`
    [[ $RunningJobs == "" ]] && break
done

echo -e 'All looper jobs done!\a'

# Local merge for the v25_9 babies
pushd ${OUTDIR}
hadd -f ttbar_25ns.root    ttbar_*Lept*.root > /dev/null
hadd -f singleT_25ns.root  t_tW_*.root  > /dev/null
hadd -f Vjets_25ns.root    W1Jets*.root W2Jets*.root W3Jets*.root W4Jets*.root > /dev/null
hadd -f rare_25ns.root     TTZ*.root WZ*.root  > /dev/null
hadd -f allBkg_25ns.root   ttbar_25ns.root singleT_25ns.root Vjets_25ns.root rare_25ns.root > /dev/null
hadd -f SMS_T2tt.root      SMS_T2tt_mStop_400to1200_madgraph_?.root > /dev/null
hadd -f SMS_T2bW.root      SMS_T2bW_madgraph_?.root > /dev/null
hadd -f SMS_T2bt.root      SMS_T2bt_madgraph_?.root > /dev/null
hadd -f allData_25ns.root  data_2016*.root > /dev/null
rm SMS_T2*_madgraph_?.root
popd > /dev/null

# Local merge for the moriond17 samples
# pushd output/temp14
# hadd -f ttbar_25ns.root    ttbar*Lept*.root > /dev/null
# hadd -f singleT_25ns.root  t_t*_noHadDecays*.root t*_4f_*.root > /dev/null
# hadd -f Vjets_25ns.root    W?Jets*.root DYJets*m10To50*.root > /dev/null
# hadd -f rare_25ns.root     ttZ*.root WZ*.root ttW*.root WW*.root ZZ*.root > /dev/null
# hadd -f allBkg_25ns.root   ttbar_25ns.root singleT_25ns.root Vjets_25ns.root rare_25ns.root > /dev/null
# popd > /dev/null

# # Temporary merge for toptagging studies
# pushd output/temp11
# cp ttbar_diLept.root ttbar_2lep.root
# hadd -f ttbar_1lep.root  ttbar_singleLept*.root > /dev/null
# hadd -f SMS_T2tt.root    SMS_T2tt_mStop_400to1200_madgraph_?.root > /dev/null
# popd > /dev/null

echo -e 'All merge jobs done!\a'
