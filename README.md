# ProyectoAraya

### README.md

#### 1. Clonar el Repositorio (solo la primera vez)/

Si aún no has clonado el repositorio, hazlo así (se hace 1 vez):

```sh
git clone https://github.com/XaxavierJS/ProyectoAraya.git
cd proyecto_c
```

#### 2. Sincronizar con el Repositorio Remoto

Antes de hacer cualquier cambio, asegúrate de que tu repositorio local esté actualizado con la última versión del repositorio remoto. Esto previene conflictos y asegura que estés trabajando con la versión más reciente del código.

```sh
git pull origin main
```

#### 3. Crear una Nueva Rama

Para trabajar en una nueva funcionalidad o corrección de errores, crea una nueva rama a partir de la rama principal:

```sh
git checkout -b nueva-funcionalidad
```

#### 4. Realizar Cambios y Commit

Haz los cambios necesarios en tu código. Luego, añade esos cambios al área de preparación (staging area) y realiza un commit:

```sh
git add nombre-archivo.c  # Añade los archivos modificados al área de preparación
git commit -m "Descripción de los cambios realizados"
```

#### 5. Sincronizar Nuevamente con la Rama Principal (Opcional pero Recomendado)

Antes de enviar tus cambios, es una buena práctica sincronizar nuevamente tu rama con la rama principal para asegurarte de que no haya nuevos cambios que puedan causar conflictos:

```sh
git pull origin main  # Vuelve a sincronizar tu rama local con la última versión de 'main'
```

#### 6. Enviar los Cambios al Repositorio Remoto

Envía tu nueva rama al repositorio remoto:

```sh
git push origin nueva-funcionalidad
```

#### 7. Crear un Pull Request en GitHub

En GitHub, navega al repositorio y crea un Pull Request desde tu rama `nueva-funcionalidad` hacia la rama `main`. Describe los cambios y solicita una revisión de tus compañeros.

### Resumen del Flujo de Trabajo

1. **Clonar el repositorio** (solo la primera vez).
2. **Sincronizar con el repositorio remoto** usando `git pull origin main`.
3. **Crear una nueva rama** para trabajar en nuevas funcionalidades o correcciones de errores.
4. **Realizar cambios, añadir, y comitear** los cambios.
5. **Sincronizar nuevamente con la rama principal** (opcional pero recomendado).
6. **Enviar los cambios al repositorio remoto**.
7. **Crear un Pull Request** en GitHub.

Este flujo asegura que siempre trabajes con la versión más reciente del código y ayuda a gestionar los cambios de manera eficiente con tu equipo.

### Comandos Resumidos

1. **Clonar el repositorio:**

   ```sh
   git clone https://github.com/tu-usuario/proyecto_c.git
   cd proyecto_c
   ```

2. **Crear una nueva rama:**

   ```sh
   git checkout -b nombre-rama
   ```

3. **Añadir y comitear cambios:**

   ```sh
   git add nombre-archivo.c
   git commit -m "Descripción de los cambios"
   ```

4. **Sincronizar con el repositorio remoto:**

   ```sh
   git pull origin master
   ```

5. **Enviar los cambios al repositorio remoto:**

   ```sh
   git push origin nombre-rama
   ```

6. **Crear un Pull Request en GitHub.**

### Notas Adicionales

- **Mantén tu código limpio y bien documentado.**
- **Realiza commits frecuentemente con mensajes claros.**
- **Comunica cualquier problema o duda con tu equipo.**

## Glosario de términos

1. **Git**: Un sistema de control de versiones distribuido que permite a los desarrolladores rastrear y gestionar cambios en el código fuente de un proyecto.
2. **Repositorio (Repository)**: Un lugar donde se almacena todo el historial de versiones y archivos de un proyecto. Puede ser local (en tu máquina) o remoto (en un servidor como GitHub).
3. **Commit**: Un registro de cambios en Git. Representa una instantánea del estado de tu proyecto en un momento dado, junto con un mensaje descriptivo.
4. **Branch (Rama)**: Una línea de desarrollo independiente en un repositorio. Las ramas permiten trabajar en características o problemas específicos sin afectar la rama principal.
5. **Master (Main)**: La rama principal de un proyecto Git. Es donde se encuentra la versión estable y funcional del código.
6. **Clone (Clonar)**: Hacer una copia de un repositorio remoto en tu máquina local para que puedas trabajar en él.
7. **Push (Empujar)**: Enviar tus commits locales a un repositorio remoto, actualizando así la versión remota del proyecto.
8. **Pull (Tirar)**: Descargar los cambios del repositorio remoto a tu máquina local para mantenerla actualizada.
