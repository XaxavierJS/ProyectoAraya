# ProyectoAraya

### README.md

## Proyecto en C con Git y GitHub

Este documento proporciona una guía paso a paso para iniciar y colaborar en un proyecto en C utilizando Git y GitHub.

### Pasos para Iniciar el Proyecto

#### 1. Clonar el Repositorio

Para obtener la última versión del código, clona el repositorio de GitHub en tu máquina local:

```sh
git clone https://github.com/tu-usuario/proyecto_c.git
cd proyecto_c
```

#### 3. Hacer Cambios y Commit

Realiza los cambios necesarios en los archivos del proyecto. Después, añade y comitea tus cambios:

```sh
git add nombre-archivo.c
git commit -m "Descripción de los cambios realizados"
```

#### 4. Sincronizar con el Repositorio Remoto

Para mantener tu rama actualizada con la rama principal del repositorio remoto, utiliza el siguiente comando:

```sh
git pull origin master
```

#### 5. Enviar los Cambios al Repositorio Remoto

Una vez que tus cambios están listos, envía tu rama al repositorio remoto:

```sh
git push origin nombre-rama
```

## Glosario de términos

1. **Git**: Un sistema de control de versiones distribuido que permite a los desarrolladores rastrear y gestionar cambios en el código fuente de un proyecto.
2. **Repositorio (Repository)**: Un lugar donde se almacena todo el historial de versiones y archivos de un proyecto. Puede ser local (en tu máquina) o remoto (en un servidor como GitHub).
3. **Commit**: Un registro de cambios en Git. Representa una instantánea del estado de tu proyecto en un momento dado, junto con un mensaje descriptivo.
4. **Branch (Rama)**: Una línea de desarrollo independiente en un repositorio. Las ramas permiten trabajar en características o problemas específicos sin afectar la rama principal.
5. **Master (Main)**: La rama principal de un proyecto Git. Es donde se encuentra la versión estable y funcional del código.
6. **Clone (Clonar)**: Hacer una copia de un repositorio remoto en tu máquina local para que puedas trabajar en él.
7. **Push (Empujar)**: Enviar tus commits locales a un repositorio remoto, actualizando así la versión remota del proyecto.
8. **Pull (Tirar)**: Descargar los cambios del repositorio remoto a tu máquina local para mantenerla actualizada.
