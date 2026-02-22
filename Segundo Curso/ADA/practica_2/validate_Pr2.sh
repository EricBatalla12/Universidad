#!/bin/bash

#ADA 2025-26
#Validación del archivo de la práctica 2 que se pretende entregar
#       USAGE: $0 tar-gz-file [-h] [--debug] [--quiet] [-d dir_home]

# BITS DEL CODIGO DE RETORNO:  _ _
#                              | |
#                              | -> No se admite la entrega ( o fichero inexistente)
#                              | -> Se han producido AVISOS (se permite la entrega pero mermará la nota)


export PATH=$PATH:.

#####  GESTION DE LA ORDEN 'timeout' ######################
MIN_TIME=5
MAX_TIME=21

# TIMEOUT: Linux/macOS compatible
# - Linux usually has 'timeout'
# - On macOS, if coreutils is installed, it is usually called 'gtimeout'
TIMEOUT_BIN=""
if command -v timeout >/dev/null 2>&1; then
    TIMEOUT_BIN="timeout"
elif command -v gtimeout >/dev/null 2>&1; then
    TIMEOUT_BIN="gtimeout"
fi

if [[ -n "$TIMEOUT_BIN" ]]; then
    TIMEOUT="${TIMEOUT_BIN} ${MAX_TIME}"
else
    echo
    echo "ATENCIÓN: No se detecta la orden 'timeout' en tu sistema. La validación se tendrá que realizar sin hacer uso de esa orden, pero ten en cuenta que en la corrección sí se hará uso de ella."
    echo
    echo "(con las pruebas que se hacen en esta validación, no se permitirá que el programa produzca violaciones de segmento o que tarde demasiado. Si ocurre alguna de estas circunstancias se asumirá que la validación es NEGATIVA. La orden 'timeout' se utiliza para detectar estos casos.)"
    echo
    TIMEOUT=""
fi

# Time in milliseconds (Linux/macOS)
now_ms() {
    if command -v gdate >/dev/null 2>&1; then
        gdate +%s%3N
    else
        local t=""
        t=$(date +%s%3N 2>/dev/null) || t=""
        if [[ "$t" =~ ^[0-9]+$ ]]; then
            echo "$t"
        else
            # Fallback portable (macOS): perl Time::HiRes
            perl -MTime::HiRes=time -e 'printf "%.0f", time()*1000'
        fi
    fi
}


# variables to be assigned in each job
num_practica="2"
source="qs-vs-hs.cc"
exe="qs-vs-hs"
err_file="errors_pr2.log"
warn_file="warnings_pr2.log"
in_tgz_must_be_files="${source} makefile qs-vs-hs.gpi"
allowed_files="${in_tgz_must_be_files} ${err_file} ${warn_file}"
objectives_makefile="all qs-vs-hs qs-vs-hs.Msteps graphs"
make_must_build="${in_tgz_must_be_files} ${exe} qs-vs-hs.Msteps fit.log quickSort.png heapSort.png qs-vs-hs-RA.png qs-vs-hs-SA.png qs-vs-hs-RSA.png"


#Control variables
#[ ! -z ${TIMEOUT} ] && { TIMEOUT="${TIMEOUT} ${MAX_TIME}"; }
RETURN_CODE=0
allowed_ext=".tar.gz .tgz"
warnings=0
name="<unknown>"
captured=""
msg_timeout=""
check_num=0

filename=""     #file (tgz) to validate
dir_home=$(pwd) #directory where is TEST subdirectory. Assumed current directory
dir_tgz=""      #directory where tgz is
quiet=0
debug=0

#argument management
args=( "$@" )
for ((i=0; i<${#args[@]}; i++)); do
    is_filename=1
    [[ ${args[$i]} == "--debug" ]] && { debug=1; is_filename=0; }
    [[ ${args[$i]} == "--quiet" ]] && { quiet=1; is_filename=0; }
    [[ ${args[$i]} == "-d" ]] && { i=$((i+1)); dir_home=${args[$i]}; is_filename=0; }
    [[ ${args[$i]} == "-h" ]] && { echo "help: $0 tar.gz-file [-h] [--debug] [--quiet] [-d dir_home]";  exit 255; }
    [[ $is_filename -eq 1 ]] && filename="${args[$i]}"
done

[[ $quiet -eq 0 ]] && echo "Entrega de la práctica ${num_practica}"
[[ $quiet -eq 0 ]] && echo "Fichero a validar: ${filename}"

[   -z "$filename" ] && { echo $0: missing tar.gz file; exit 255; }
[ ! -f "$filename" ] && { echo $0: file \'$filename\' not found; exit 255; }



#Create tmp directory
tmp_dir=$(mktemp -d /tmp/validate_dir.XXXXXX)

# Actions at the end
by_the_end() {
    exit_code=$?
    [[ -f ${err_file} ]] && exit_code=1
    [[ -f ${warn_file} ]] && { warnings=1; RETURN_CODE=$(( RETURN_CODE |= 2 )); }
    [[ $exit_code -ne 0 ]] && RETURN_CODE=$((RETURN_CODE |= 1))
    if [[ $quiet -eq 0 ]]; then
        [[ -f ${warn_file} ]] && { echo; cat ${warn_file}; }
        [[ $warnings  -ne 0 ]] && echo -e "\nATENCIÓN: Los avisos mostrados pueden mermar considerablemente la nota."
        [[ -f ${err_file} ]] && { echo; cat ${err_file}; }
        if [[ $exit_code -eq 0 ]]; then
            echo -e "\nDNI/NIE asociado al archivo comprimido: "$dni
            echo -e "Nombre capturado en la primera línea de ${source}: "$name
            echo -e "Asegúrate de que la captura mostrada  de DNI/NIE y nombre es correcta."
            echo -e "\nVALIDACIÓN POSITIVA: El trabajo cumple las especificaciones básicas (no se comprueban todas), pero asegúrate de que también compila en los ordenadores del aula."
        else
            echo -e "\nVALIDACIÓN NEGATIVA: Debes corregir los errores antes de entregar."
        fi
#    else
#        echo -n $RETURN_CODE
    fi
    rm -rf -- "$tmp_dir"
    exit $RETURN_CODE
}



check_err_args() {
    error_message=$($1 2>&1 1>/dev/null)
    ret=$? # 124=timeout; 134=seg-fault; 139=core-dumped
    if [[ $ret -eq 124 ]] || [[ $ret -eq 134 ]] || [[ $ret -eq 139 ]]; then
        echo "Aviso: '$2' produce violación de segmento o 'timeout'" >> ${warn_file}
        warnings=1
    fi
    if [[ -z "$error_message" ]]; then
        echo "Aviso: '$2' no emite mensaje de error (por la salida de error)"  >> ${warn_file}
        warnings=1
    fi 
    [[ $warnings -eq 1 ]] &&  RETURN_CODE=$(( RETURN_CODE |= 2 ))
}

check_code() {
    gprof -p -b $1 gmon.out | grep $2
    if [ $? -ne 0 ]; then
        check_call_funct $2
    fi
    check_memory_map --save $1 $2    
}

error_msg(){
    echo -e "\n*** Validación número $3 ***" >> ${err_file}
    echo -e "  Prueba realizada: $2" >> ${err_file}
    echo -e "  $1" >> ${err_file}
    RETURN_CODE=$(( RETURN_CODE |= 1 ))
}

launch() {
    [[ -f tmp_file ]] && rm tmp_file
    captured=$($1 2>tmp_file); ret=$?
    case $ret in
	    124) msg_timeout="tarda demasiado ('timeout').";;
	    134) msg_timeout="produce violación de segmento.";;
	    139) msg_timeout="produce un 'core'.";;
	    *)   [[ -s tmp_file ]] && { msg_timeout="no debe mostrar nada por la salida de error puesto que es correcta."; ret=1; } || ret=0
    esac
    [[ $ret -ne 0 ]] && error_msg "Error: la orden ${msg_timeout}" "$2" $3
    return $ret
}

function validate_n_nums() {
# códigos de error: 
#   1:más elementos de lo especificado  $2; 
#   2:alguno de los elementos no son números
captured_array=()
read -a captured_array < <(echo $1)
[[ ${#captured_array[@]} -ne $2 ]] && return 1
d=[0-9]
for ((i=0; i<${#captured_array[@]}; i++)); do
    [[ ! ${captured_array[i]} =~ ^$d+([.]$d+)?([Ee][-+]?$d+)?$ ]] && return 2
done
return 0
}


#capture signals
#trap by_the_end EXIT SIGINT SIGTERM
trap by_the_end EXIT
trap 'exit 130' SIGINT
trap 'exit 143' SIGTERM



# Work in tmp dir; capture tgz name and directory where it is
cp "$filename" $tmp_dir
cd "$(dirname "${filename}")"
dir_tgz=$(pwd)
filename="$(basename "${filename}")" #filename=${filename##*/}
cd $tmp_dir



# dni/nie & extension of the file to be delivered
check_num=1
dni=$(echo "$filename" | cut -d "." -f 1)
ext=.$(echo "$filename" | cut -d "." -f 2-3) # | tr -d '\n' | tail -c 2)
if [[ ! " $allowed_ext " =~ " $ext " ]];then
    echo "Error: Las extensiones permitidas son: {"$allowed_ext"}."  >> ${err_file}
    echo -e "\t(extensión capturada: $ext )" >> ${err_file}
    RETURN_CODE=$((RETURN_CODE |= 1))
    exit 1
fi

# unpack tgz
check_num=2
tar -tzf "$filename" | grep -E '(^/|^\.\./|/\.{2}/)' && {
  echo "Error: el .tgz contiene rutas no permitidas." >> "$err_file"
  exit 1
}
tar -xzf "$filename" > /dev/null
if [ $? -ne 0 ]; then
    echo "Error: 'tar' falló al desempaquetar ${filename}." >> ${err_file}
    RETURN_CODE=$((RETURN_CODE |= 1))
    exit 1
fi

# keep only what is stored in the tgz
rm "$filename"
[[ -f ${err_file}  ]] && rm ${err_file}
[[ -f ${warn_file} ]] && rm ${warn_file}


# Verify that has been delivered what is requested
check_num=3
missing=""
for f in ${in_tgz_must_be_files}; do
    if [ ! -f $f ]; then
        missing=${missing}" "${f}
    fi 
done
if [[ ! -z ${missing} ]]; then
    echo "Error: Falta/n archivo/s en la entrega (${missing} )." >> ${err_file}
    RETURN_CODE=$((RETURN_CODE |= 1))
fi



# verify that only what is necessary is delivered
check_num=4
unwanted=""
[[ -f Makefile ]] && mv Makefile makefile
for f in *; do
    if [[ ! " $allowed_files " =~ " $f " ]];then 
        unwanted=${unwanted}" "${f}
    fi
done
if [[ ! -z ${unwanted} ]]; then
    echo "Error: Se entregan más archivos de los permitidos (${unwanted} )." >> ${err_file}
    RETURN_CODE=$((RETURN_CODE |= 1))
fi


#name="$(echo -e "${name}" | sed -e 's/^[[:space:]]*//' -e 's/[[:space:]]*$//')" # All-TRIM
#tr -d "[:space:]" #elimina tb saltos de linea, a diferencia de tr -d "" que elimina solo espacios
# Verify the student's name in the first line of the source (only first line is checked)
check_num=5
[[ ! -f ${source} ]] && { RETURN_CODE=$((RETURN_CODE |= 1)); exit 1; }
name=$(cat ${source} | head -n 1 | tr '*' '/' | xargs)
[[ "$name" =~ ^"//" ]] && name=$(echo ${name} | tr -d '/' | xargs) || name="<unknown>"
[[ -z ${name} ]] && name="<unknown>"
if [[ "$name" == "<unknown>" ]]; then
    echo "Error: No se captura tu nombre en la primera línea del archivo ${source}." >> ${err_file}
    RETURN_CODE=$((RETURN_CODE |= 1))
fi

#compilation
check_num=6
start_ms=$(now_ms)
$TIMEOUT make all &> /dev/null
ret=$?
end_ms=$(now_ms)
elapsed_ms=$((end_ms - start_ms))
MIN_TIME_MS=$((MIN_TIME * 1000))

[ $quiet -eq 0 ] && echo -n "Tiempo de proceso (ms.): "; [ $ret -eq 124 ]  && echo -n "TIMEOUT(${MAX_TIME} seg.)" || echo -n ${elapsed_ms}
case $ret in
    124) msg_timeout="'make' se lleva un tiempo excesivo (> ${MAX_TIME} seg.)";;
    134) msg_timeout="El programa produce una violación de segmento";;
    139) msg_timeout="El programa produce una violación de segmento";;
    *)   [[ $ret -ne 0 ]] && msg_timeout="'make' ha fallado ($ret)";;
esac
[[ $ret -ne 0 ]] && { echo Error: $msg_timeout >> ${err_file}; RETURN_CODE=$((RETURN_CODE |= 1)); exit 1; }

# 'make all' is too fast!
if (( elapsed_ms < MIN_TIME_MS )); then
    echo "Aviso: ejecución sospechosamente rápida (${elapsed_ms} ms < ${MIN_TIME_MS} ms). Posible falta de repeticiones o carga de instancias." >> "$warn_file"
fi

# verify that 'make' builds all files
check_num=7
are_not=""
for f in ${make_must_build}; do
    if [ ! -f $f ]; then
         are_not=${are_not}" "${f}
    fi 
done
if [[ ! -z ${are_not} ]]; then
    echo "Error: 'make' no crea todo los archivos que se piden (${are_not})." >> ${err_file}
    RETURN_CODE=$((RETURN_CODE |= 1))
fi

# verify objectives in makefile
check_num=8
fault=""
for o in ${objectives_makefile}; do
    make -t ${o} &>/dev/null
    if [[ $? -ne 0 ]]; then
         fault=${fault}" "${o}
    fi 
done
if [[ ! -z ${fault} ]]; then
    echo "Error: Alguno de los objetivos del 'makefile' han fallado (${fault})." >> ${err_file}
    RETURN_CODE=$((RETURN_CODE |= 1))
fi


# verify qs-vs-hs.Msteps file (6 rows, expected sizes, 6 data columns)
check_num=9
msteps_file="qs-vs-hs.Msteps"

    expected_sizes=(32768 65536 131072 262144 524288 1048576)
    row=0

    # Read file line by line
    while IFS= read -r line; do
        # Skip comments and empty lines
        [[ -z "$line" ]] && continue
        [[ "$line" == \#* ]] && continue

        # Data lines start with a number (possibly preceded by spaces)
        if [[ "$line" =~ ^[[:space:]]*[0-9]+[[:space:]] ]]; then
            # Split into fields
            set -- $line

            # Must be 7 columns: Size + 6 values
            if (( $# != 7 )); then
                echo "Error: Formato incorrecto en ${msteps_file} (se esperaban 7 columnas). Línea: $line" >> "${err_file}"
                RETURN_CODE=$((RETURN_CODE |= 1))
                exit 1
            fi

            # Check expected size (and exactly 6 rows)
            if (( row >= 6 )); then
                echo "Error: Hay más de 6 filas de datos en ${msteps_file}." >> "${err_file}"
                RETURN_CODE=$((RETURN_CODE |= 1))
                exit 1
            fi

            size="$1"
            if [[ "$size" != "${expected_sizes[$row]}" ]]; then
                echo "Error: Tamaño incorrecto en fila $((row+1)) de ${msteps_file}. Esperado ${expected_sizes[$row]} y encontrado ${size}." >> "${err_file}"
                RETURN_CODE=$((RETURN_CODE |= 1))
                exit 1
            fi

            # Check that the 6 data values are numeric (decimal dot)
            for v in "$2" "$3" "$4" "$5" "$6" "$7"; do
                if [[ ! "$v" =~ ^[0-9]+([.][0-9]+)?$ ]]; then
                    echo "Error: Valor no numérico en ${msteps_file} (fila $((row+1))). Valor: ${v}." >> "${err_file}"
                    RETURN_CODE=$((RETURN_CODE |= 1))
                    exit 1
                    #break
                fi
            done

            row=$((row+1))
        fi
    done < "$msteps_file"

    # Must have exactly 6 data rows
    if (( row != 6 )); then
        echo "Error: Se han detectado ${row} filas de datos en ${msteps_file}, pero deben ser exactamente 6." >> "${err_file}"
        RETURN_CODE=$((RETURN_CODE |= 1))
        exit 1
    fi




# verify number of fits 
check_num=10
nfits_must_be=6
[[ ! -f fit.log ]] && { echo "Error: no se crea el archivo fit.log (lo debería crear la llamada a gnuplot)." >> ${err_file}; RETURN_CODE=$((RETURN_CODE|=1)); exit 1; }
num_fits=$(cat fit.log | grep fitting | wc -l)
[[ $num_fits -ne $nfits_must_be ]] && { echo "Error: El número de ajustes mmcc que se piden es exactamente $nfits_must_be." >> ${err_file}; RETURN_CODE=$((RETURN_CODE |= 1)); exit 1; }


# verify fit function (check all fits in fit.log)
check_num=11
found=0
idx=0
# Iterate over all occurrences and check the next line (function definition)
while IFS= read -r ln; do
    found=1
    idx=$((idx+1))

    # Read the next line after "function used for fitting:"
    func_line=$(sed -n "$((ln+1))p" fit.log)

    # Normalize: remove spaces and lowercase
    func=$(printf '%s' "$func_line" | tr -d ' ' | tr '[:upper:]' '[:lower:]')

    # Extract variable name inside (...) from something like f(x)=...
    var=$(printf '%s' "$func" | sed -nE 's/.*\(([a-z_][a-z0-9_]*)\).*/\1/p')
    [[ -z "$var" ]] && var="x"

    # Detect quadratic patterns that must NOT appear
    quad_re="(${var}\\*${var}|${var}\\^2|${var}\\*\\*2|pow\\(${var},2\\))"

    # Detect required n log n term (must appear at least once)
    logterm_re="(${var}\\*log[0-9]*\\(${var}\\)|log[0-9]*\\(${var}\\)\\*${var})"

    if [[ "$func" =~ $quad_re ]] || [[ ! "$func" =~ $logterm_re ]]; then
        echo "Error: La función de ajuste utilizada no es correcta (ajuste #${idx})." >> "${err_file}"
        RETURN_CODE=$((RETURN_CODE |= 1))
        exit 1
    fi
done < <(grep -n -F "function used for fitting:" fit.log | cut -d: -f1)

if [[ $found -eq 0 ]]; then
    echo "Error: No se ha encontrado ninguna sección 'function used for fitting' en fit.log." >> "${err_file}"
    RETURN_CODE=$((RETURN_CODE |= 1))
    exit 1
fi


# verify that every fit attempt produced a "Final set of parameters" block
check_num=12
    current_fit=""
    current_has_final=0
    failed_fits=""

    while IFS= read -r line; do
        # New fit starts here
        if [[ "$line" == *"function used for fitting:"* ]]; then
            # Close previous fit section (if any)
            if [[ -n "$current_fit" && $current_has_final -eq 0 ]]; then
                failed_fits+="${current_fit},"
            fi

            # Capture fit name (e.g., ra2(x))
            current_fit="${line#*function used for fitting: }"
            current_fit="$(printf '%s' "$current_fit" | xargs)"
            current_has_final=0
            continue
        fi

        # Mark that this fit produced final parameters
        if [[ "$line" == *"Final set of parameters"* ]]; then
            current_has_final=1
            continue
        fi
    done < fit.log

    # Close last fit section
    if [[ -n "$current_fit" && $current_has_final -eq 0 ]]; then
        failed_fits+="${current_fit},"
    fi

    if [[ -n "$failed_fits" ]]; then
        failed_fits="${failed_fits%,}"
        echo "Error: Algún ajuste (fit) no ha generado 'Final set of parameters' (no ha convergido o no se ha completado): ${failed_fits}." >> "${err_file}"
        RETURN_CODE=$((RETURN_CODE |= 1))
        exit 1
    fi

#check_num=13
# verify that parameter names do not overlap between each pair of fits
# First: extract_fit_coeffs_all():
#Extract coefficient names from each "Final set of parameters" block in fit.log
#
extract_fit_coeffs_all() {
  local file="${1:-fit.log}"
  local in_block=0
  local got_any=0
  local out=""

  while IFS= read -r line; do
    if [[ "$line" == *"Final set of parameters"* ]]; then
      # If we were already collecting, flush previous block (rare)
      if (( in_block == 1 )) && (( got_any == 1 )); then
        echo "${out%,}"
      fi
      in_block=1
      got_any=0
      out=""
      continue
    fi

    if (( in_block == 1 )); then
      # Stop at the first blank line after parameters
      if [[ -z "$line" ]]; then
        if (( got_any == 1 )); then
          echo "${out%,}"
        fi
        in_block=0
        got_any=0
        out=""
        continue
      fi

      # Ignore underline/header lines (==== or similar)
      [[ "$line" =~ ^[=[:space:]]+$ ]] && continue

      # Parameter lines look like:  name = value ...
      if [[ "$line" =~ ^[[:space:]]*([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*= ]]; then
        out+="${BASH_REMATCH[1]},"
        got_any=1
      fi
    fi
  done < "$file"

  # Flush last block if file ended without trailing blank line
  if (( in_block == 1 )) && (( got_any == 1 )); then
    echo "${out%,}"
  fi
}

check_num=13
    # Read coefficient lists into array
    mapfile -t coeff_lines < <(extract_fit_coeffs_all fit.log)

    # Must be even number of fits
    if (( ${#coeff_lines[@]} % 2 != 0 )); then
        echo "Error: Número impar de ajustes detectados. Deben hacerse por parejas." >> "${err_file}"
        RETURN_CODE=$((RETURN_CODE |= 1))
        exit 1
    fi

    # Compare pairs
    bad=0
    for ((i=0; i+1<${#coeff_lines[@]}; i+=2)); do
        p1="${coeff_lines[$i]}"
        p2="${coeff_lines[$i+1]}"

        # Build set of p1
        declare -A seen=()
        IFS=',' read -r -a a1 <<< "$p1"
        for v in "${a1[@]}"; do
            [[ -n "$v" ]] && seen["$v"]=1
        done

        # Check overlap with p2
        overlap=""
        IFS=',' read -r -a a2 <<< "$p2"
        for v in "${a2[@]}"; do
            if [[ -n "${seen[$v]}" ]]; then
                overlap+="${v},"
            fi
        done

        unset seen

        if [[ -n "$overlap" ]]; then
            overlap="${overlap%,}"
            echo "Error: En la pareja de ajustes $((i/2+1)) se reutilizan coeficientes (${overlap}). Deben ser distintos para no machacarse." >> "${err_file}"
            bad=1
        fi
    done
    if (( bad == 1 )); then
            RETURN_CODE=$((RETURN_CODE |= 1))
            exit 1
    fi


# warn if fit is not of the form x*log(x) + x + k
check_num=14
    idx=0

    while IFS= read -r ln; do
        idx=$((idx+1))

        # Get the function definition line (next line)
        func_line=$(sed -n "$((ln+1))p" fit.log)

        # Normalize: remove spaces and lowercase
        func=$(printf '%s' "$func_line" | tr -d ' ' | tr '[:upper:]' '[:lower:]')

        # Extract variable name inside (...) from f(var)=...
        var=$(printf '%s' "$func" | sed -nE 's/.*\(([a-z_][a-z0-9_]*)\).*/\1/p')
        [[ -z "$var" ]] && var="x"

        # Detect forbidden quadratic patterns
        is_quadratic=0
        [[ "$func" =~ (${var}\*${var}|${var}\^2|${var}\*\*2|pow\(${var},2\)) ]] && is_quadratic=1

        # Require coefficient for var*logk(var):
        # Accept: a*var*logk(var) OR a*logk(var)*var OR var*logk(var)*a OR logk(var)*var*a
        has_xlog_coef=0
        [[ "$func" =~ ([+\-]|=)[a-z_][a-z0-9_]*\*${var}\*log[0-9]*\(${var}\) ]] && has_xlog_coef=1
        [[ "$func" =~ ([+\-]|=)[a-z_][a-z0-9_]*\*log[0-9]*\(${var}\)\*${var} ]] && has_xlog_coef=1
        [[ "$func" =~ ${var}\*log[0-9]*\(${var}\)\*[a-z_][a-z0-9_]* ]] && has_xlog_coef=1
        [[ "$func" =~ log[0-9]*\(${var}\)\*${var}\*[a-z_][a-z0-9_]* ]] && has_xlog_coef=1

        # Remove xlog terms before searching for the linear term (prevents false positives)
        func_wo_xlog=$(printf '%s' "$func" | sed -E \
          "s/[a-z_][a-z0-9_]*\\*${var}\\*log[0-9]*\\(${var}\\)//g; \
           s/[a-z_][a-z0-9_]*\\*log[0-9]*\\(${var}\\)\\*${var}//g; \
           s/${var}\\*log[0-9]*\\(${var}\\)\\*[a-z_][a-z0-9_]*/ /g; \
           s/log[0-9]*\\(${var}\\)\\*${var}\\*[a-z_][a-z0-9_]*/ /g")

        # Require coefficient for linear term b*var OR var*b (NOT bare +var)
        has_x_coef=0
        [[ "$func_wo_xlog" =~ ([+\-]|=)[a-z_][a-z0-9_]*\*${var} ]] && has_x_coef=1
        [[ "$func_wo_xlog" =~ ([+\-]|=)${var}\*[a-z_][a-z0-9_]* ]] && has_x_coef=1

        # Require independent constant term (+c or -c at the end)
        has_const=0
        [[ "$func" =~ [+\-][a-z_][a-z0-9_]*$ ]] && has_const=1

        # Emit WARNING (maybe is not an error) if model is not satisfied
        if (( is_quadratic == 1 || has_xlog_coef == 0 || has_x_coef == 0 || has_const == 0 )); then
            echo "ATENCIÓN: El ajuste #${idx} no sigue el modelo a*${var}*log(${var}) + b*${var} + c (tres coeficientes, uno por término)." >> "${warn_file}"
            warnings=1
            RETURN_CODE=$((RETURN_CODE |= 2))
        fi

    done < <(grep -n -F "function used for fitting:" fit.log | cut -d: -f1)


( [[ -f ${err_file} ]] || [[ $((RETURN_CODE&1)) -eq 1 ]] ) && exit 1;

exit 0


